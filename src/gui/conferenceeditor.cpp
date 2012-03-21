/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann
 *
 * This file is part of ConfClerk.
 *
 * ConfClerk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * ConfClerk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ConfClerk.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "conferenceeditor.h"

#include "conferencemodel.h"
#include "urlinputdialog.h"
#include "errormessage.h"

#include <QInputDialog>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QMessageBox>

ConferenceEditor::ConferenceEditor(ConferenceModel* model, QWidget* parent)
: QDialog(parent)
, model(model)
, selected_id(-1)
{
    setupUi(this);
    progressBar->hide();

    confView->setModel(model);

    QItemSelectionModel* confViewSelection = new QItemSelectionModel(model, this);
    confView->setSelectionModel(confViewSelection);

    connect(confViewSelection, SIGNAL(currentChanged(const QModelIndex&, const QModelIndex&)),
                                SLOT(itemSelected(const QModelIndex&, const QModelIndex&)));
    connect(this, SIGNAL(wantCurrent(const QModelIndex&, QItemSelectionModel::SelectionFlags)),
            confViewSelection, SLOT(setCurrentIndex(const QModelIndex&, QItemSelectionModel::SelectionFlags)));
    connect(addBtn, SIGNAL(clicked()), SLOT(addClicked()));
    connect(removeBtn, SIGNAL(clicked()), SLOT(removeClicked()));
    connect(changeUrl, SIGNAL(clicked()), SLOT(changeUrlClicked()));
    connect(refreshBtn, SIGNAL(clicked()), SLOT(refreshClicked()));
    connect(buttonBox, SIGNAL(rejected()), SLOT(close()));

    // it's OK to emit selection signals here
    // because they are not yet connected to anybody
    int active_id = Conference::activeConference();
    if (active_id > 0) {
        emit wantCurrent(model->indexFromId(active_id), QItemSelectionModel::SelectCurrent);
    } else {
        itemSelected(QModelIndex(), QModelIndex());
    }
}

void ConferenceEditor::conferenceRemoved()
{
    if (model->rowCount() > 0) {
        emit wantCurrent(model->index(0, 0), QItemSelectionModel::SelectCurrent);
    } else {
        itemSelected(QModelIndex(), QModelIndex());
    }
}

void ConferenceEditor::itemSelected(const QModelIndex& current, const QModelIndex& previous)
{
    // TODO: fill all required fields
    Q_UNUSED(previous);
    if (!current.isValid()) {
        selected_id = -1;

        emit noneConferenceSelected();

        conferenceInfo->setCurrentIndex(1);
        removeBtn->hide();
    } else {
        const Conference& conf = model->conferenceFromIndex(current);
        selected_id = conf.id();

        emit haveConferenceSelected(selected_id);

        conferenceTitle->setText(conf.title());
        conferenceSubtitle->setText(conf.subtitle());
        conferenceWhere->setText(conf.city() + (!conf.venue().isEmpty() ? ", " + conf.venue() : ""));
        conferenceWhen->setText(
                conf.start().toString("yyyy-MM-dd")
                + " - " +
                conf.end().toString("yyyy-MM-dd"));
        conferenceInfo->setCurrentIndex(0);
        removeBtn->show();
    }
}

void ConferenceEditor::addClicked()
{
    UrlInputDialog url_input(this);
    switch (url_input.exec()) {
    case UrlInputDialog::HaveUrl: emit haveConferenceUrl(url_input.url()); break;
    case UrlInputDialog::HaveFile: emit haveConferenceFile(url_input.url()); break;
    case UrlInputDialog::Cancel: return;
    }
}

void ConferenceEditor::removeClicked()
{
    if (selected_id < 0) {
        // TODO: disable it when none is selected
        return;
    }

    QMessageBox::StandardButton answer = 
        QMessageBox::question(0
            , "Deletion confirmation"
            , QString("Really delete the %1 conference").arg(Conference::getById(selected_id).title())
            , QMessageBox::Yes | QMessageBox::No
            , QMessageBox::No);

    if (answer == QMessageBox::Yes) {
        emit removeConferenceRequested(selected_id);
    }
}

void ConferenceEditor::changeUrlClicked()
{
    if (selected_id < 0) return;
    const Conference& selectedConf = Conference::getById(selected_id);

    bool ok;
    QString url = QInputDialog::getText(this, "URL Input", "Enter schedule URL", QLineEdit::Normal, selectedConf.url(), &ok);

    if (ok) {
        emit changeUrlRequested(selected_id, url);
    }
}

void ConferenceEditor::refreshClicked()
{
    if (selected_id < 0) return;
    const Conference& selectedConf = Conference::getById(selected_id);
    QString url = selectedConf.url();

    if (url.isEmpty()) {
        static const QString format("Schedule URL for %1 is not set. Enter the schedule URL:");
        bool ok;
        QString url = QInputDialog::getText(this, "URL Input", format.arg(selectedConf.title()), QLineEdit::Normal, QString(), &ok);
        if (!ok) return;
        // first save it, to remain if fetch fails
        emit changeUrlRequested(selected_id, url);
    }
    // fetch
    importStarted(); // just to show the progress bar
    emit haveConferenceUrl(url);
}

void ConferenceEditor::importStarted()
{
    addBtn->hide();
    removeBtn->hide();
    buttons->layout()->removeItem(buttonsSpacer);
    progressBar->setValue(0);
    progressBar->show();

    QApplication::processEvents();
}

void ConferenceEditor::showParsingProgress(int progress)
{
    progressBar->setValue(progress);

    QApplication::processEvents();
}

void ConferenceEditor::importFinished(const QString& title)
{
    addBtn->show();
    // removeItem should be shown later, but it takes some time,
    // and not looks good
    // anyway it will be shown a bit later
    removeBtn->show();
    buttons->layout()->addItem(buttonsSpacer);
    progressBar->hide();

    QApplication::processEvents();

    int num = model->rowCount();
    for (int i = 0; i < num; i++) {
        QModelIndex item = model->index(i, 0);
        if (model->data(item) == title) {
            emit wantCurrent(item, QItemSelectionModel::SelectCurrent);
            return;
        }
    }
    itemSelected(QModelIndex(), QModelIndex());
}

