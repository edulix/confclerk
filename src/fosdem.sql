BEGIN TRANSACTION;
CREATE TABLE CONFERENCE ( id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL
    , title VARCHAR UNIQUE NOT NULL
    , subtitle VARCHAR
    , venue VARCHAR
    , city VARCHAR NOT NULL
    , start INTEGER NOT NULL
    , end INTEGER NOT NULL
    , days INTEGER
    , day_change INTEGER
    , timeslot_duration INTEGER
    , active INTEGER DEFAULT 0
    , url VARCHAR UNIQUE
    , map VARCHAR);
INSERT INTO "CONFERENCE" VALUES(1,'FOSDEM 2010','Free and Opensource Software Developers European Meeting','ULB (Campus Solbosch)','Brussels',1265414400,1265500800,2,28800,900,1,"http://fosdem.org/2010/schedule/xml", ":/maps/campus.png");
CREATE TABLE TRACK ( id INTEGER  PRIMARY KEY AUTOINCREMENT  NOT NULL
    , name VARCHAR UNIQUE NOT NULL );
INSERT INTO "TRACK" VALUES(1,'Keynotes');
INSERT INTO "TRACK" VALUES(2,'Monitoring');
INSERT INTO "TRACK" VALUES(3,'Security');
INSERT INTO "TRACK" VALUES(4,'Lightning Talks');
INSERT INTO "TRACK" VALUES(5,'Embedded');
INSERT INTO "TRACK" VALUES(6,'Mozilla');
INSERT INTO "TRACK" VALUES(7,'Certification');
INSERT INTO "TRACK" VALUES(8,'Distributions');
INSERT INTO "TRACK" VALUES(9,'GNOME');
INSERT INTO "TRACK" VALUES(10,'Jabber+XMPP');
INSERT INTO "TRACK" VALUES(11,'KDE');
INSERT INTO "TRACK" VALUES(12,'JBoss');
INSERT INTO "TRACK" VALUES(13,'OpenOffice.org');
INSERT INTO "TRACK" VALUES(14,'PostgreSQL');
INSERT INTO "TRACK" VALUES(15,'Coreboot');
INSERT INTO "TRACK" VALUES(16,'Ruby+Rails');
INSERT INTO "TRACK" VALUES(17,'Free Java');
INSERT INTO "TRACK" VALUES(18,'Various');
INSERT INTO "TRACK" VALUES(19,'Scalability');
INSERT INTO "TRACK" VALUES(20,'Javascript');
INSERT INTO "TRACK" VALUES(21,'Database');
INSERT INTO "TRACK" VALUES(22,'Keysigning');
INSERT INTO "TRACK" VALUES(23,'CrossDesktop');
INSERT INTO "TRACK" VALUES(24,'Mono');
INSERT INTO "TRACK" VALUES(25,'Drupal');
INSERT INTO "TRACK" VALUES(26,'Alt-OS');
INSERT INTO "TRACK" VALUES(27,'GNUstep');
INSERT INTO "TRACK" VALUES(28,'NoSQL');
INSERT INTO "TRACK" VALUES(29,'MySQL');
INSERT INTO "TRACK" VALUES(30,'Openmoko');
INSERT INTO "TRACK" VALUES(31,'X.org');
INSERT INTO "TRACK" VALUES(32,'BSD');
CREATE TABLE ROOM ( id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL
    , name VARCHAR UNIQUE NOT NULL
    , picture VARCHAR NOT NULL);
INSERT INTO "ROOM" VALUES(1,'Janson', ':/maps/rooms/janson.png');
INSERT INTO "ROOM" VALUES(2,'Chavanne', ':/maps/rooms/chavanne.png');
INSERT INTO "ROOM" VALUES(3,'Ferrer', ':/maps/rooms/ferrer.png');
INSERT INTO "ROOM" VALUES(4,'Lameere', ':/maps/rooms/lameere.png');
INSERT INTO "ROOM" VALUES(5,'H.1301', ':/maps/rooms/h1301.png');
INSERT INTO "ROOM" VALUES(6,'UA2.114', ':/maps/rooms/ua2114.png');
INSERT INTO "ROOM" VALUES(7,'H.1302', ':/maps/rooms/h1302.png');
INSERT INTO "ROOM" VALUES(8,'H.1308', ':/maps/rooms/h1308.png');
INSERT INTO "ROOM" VALUES(9,'H.1309', ':/maps/rooms/h1309.png');
INSERT INTO "ROOM" VALUES(10,'H.2213', ':/maps/rooms/h2213.png');
INSERT INTO "ROOM" VALUES(11,'H.2214', ':/maps/rooms/h2214.png');
INSERT INTO "ROOM" VALUES(12,'AW1.105', ':/maps/rooms/aw1105.png');
INSERT INTO "ROOM" VALUES(13,'AW1.120', ':/maps/rooms/aw1120.png');
INSERT INTO "ROOM" VALUES(14,'AW1.121', ':/maps/rooms/aw1121.png');
INSERT INTO "ROOM" VALUES(15,'AW1.124', ':/maps/rooms/aw1124.png');
INSERT INTO "ROOM" VALUES(16,'AW1.126', ':/maps/rooms/aw1126.png');
INSERT INTO "ROOM" VALUES(17,'Guillissen', ':/maps/rooms/guillissen.png');
INSERT INTO "ROOM" VALUES(18,'AY', ':/maps/rooms/ay.png');
INSERT INTO "ROOM" VALUES(19,'AW1.117', ':/maps/rooms/aw1117.png');
INSERT INTO "ROOM" VALUES(20,'AW1.125', ':/maps/rooms/aw1125.png');
CREATE TABLE PERSON ( id INTEGER PRIMARY KEY  NOT NULL, name VARCHAR UNIQUE NOT NULL);
INSERT INTO "PERSON" VALUES(19,'Tias Guns');
INSERT INTO "PERSON" VALUES(22,'Peter Saint-Andre');
INSERT INTO "PERSON" VALUES(30,'Miguel de Icaza');
INSERT INTO "PERSON" VALUES(42,'Klaus Behrla');
INSERT INTO "PERSON" VALUES(46,'FOSDEM Staff');
INSERT INTO "PERSON" VALUES(51,'Dave Neary');
INSERT INTO "PERSON" VALUES(52,'Emil Ivov');
INSERT INTO "PERSON" VALUES(69,'Boriss Mejias');
INSERT INTO "PERSON" VALUES(70,'Sven Krohlas');
INSERT INTO "PERSON" VALUES(74,'Wouter Verhelst');
INSERT INTO "PERSON" VALUES(90,'Nikolaus Schaller');
INSERT INTO "PERSON" VALUES(92,'Nicolas Roard');
INSERT INTO "PERSON" VALUES(93,'Quentin Mathé');
INSERT INTO "PERSON" VALUES(95,'Bart Coppens');
INSERT INTO "PERSON" VALUES(98,'Jos Poortvliet');
INSERT INTO "PERSON" VALUES(99,'Sebastian Trüg');
INSERT INTO "PERSON" VALUES(116,'Philip Van Hoof');
INSERT INTO "PERSON" VALUES(124,'Dafydd Harries');
INSERT INTO "PERSON" VALUES(130,'Christophe Fergeau');
INSERT INTO "PERSON" VALUES(134,'Adrian Schroeter');
INSERT INTO "PERSON" VALUES(147,'Will Stephenson');
INSERT INTO "PERSON" VALUES(149,'Duncan Mac-Vicar Prett');
INSERT INTO "PERSON" VALUES(152,'Lucas Nussbaum');
INSERT INTO "PERSON" VALUES(165,'Max Spevack');
INSERT INTO "PERSON" VALUES(171,'Michael Lauer');
INSERT INTO "PERSON" VALUES(174,'Axel Hecht');
INSERT INTO "PERSON" VALUES(175,'Zbigniew Braniecki');
INSERT INTO "PERSON" VALUES(177,'Gervase Markham');
INSERT INTO "PERSON" VALUES(180,'Ludovic Hirlimann');
INSERT INTO "PERSON" VALUES(182,'Ralph Angenendt');
INSERT INTO "PERSON" VALUES(187,'Jeff Johnson');
INSERT INTO "PERSON" VALUES(193,'Dalibor Topic');
INSERT INTO "PERSON" VALUES(194,'Mark Wielaard');
INSERT INTO "PERSON" VALUES(200,'Ralph Meijer');
INSERT INTO "PERSON" VALUES(210,'Philippe Normand');
INSERT INTO "PERSON" VALUES(260,'Philip Paeps');
INSERT INTO "PERSON" VALUES(261,'Mark Finkle');
INSERT INTO "PERSON" VALUES(270,'Stephan Bergmann');
INSERT INTO "PERSON" VALUES(271,'Thorsten Behrens');
INSERT INTO "PERSON" VALUES(272,'Jürgen Schmidt');
INSERT INTO "PERSON" VALUES(280,'Jerome Glisse');
INSERT INTO "PERSON" VALUES(284,'Nicolas Jacobeus');
INSERT INTO "PERSON" VALUES(292,'Petteri Räty');
INSERT INTO "PERSON" VALUES(293,'Thomas Koch');
INSERT INTO "PERSON" VALUES(312,'Robert Douglass');
INSERT INTO "PERSON" VALUES(327,'Kris Buytaert');
INSERT INTO "PERSON" VALUES(334,'Klaas Freitag');
INSERT INTO "PERSON" VALUES(339,'Peter Poeml');
INSERT INTO "PERSON" VALUES(344,'Tristan Nitot');
INSERT INTO "PERSON" VALUES(374,'Zeeshan Ali');
INSERT INTO "PERSON" VALUES(403,'David Fetter');
INSERT INTO "PERSON" VALUES(405,'Shteryana Shopova');
INSERT INTO "PERSON" VALUES(406,'Simon Riggs');
INSERT INTO "PERSON" VALUES(415,'Magnus Hagander');
INSERT INTO "PERSON" VALUES(416,'Marius Nünnerich');
INSERT INTO "PERSON" VALUES(417,'Benny Siegert');
INSERT INTO "PERSON" VALUES(418,'Heikki Linnakangas');
INSERT INTO "PERSON" VALUES(441,'Michael Meeks');
INSERT INTO "PERSON" VALUES(457,'Frank Scholz');
INSERT INTO "PERSON" VALUES(466,'Carsten Book');
INSERT INTO "PERSON" VALUES(467,'Daniel Stone');
INSERT INTO "PERSON" VALUES(473,'Mark Surman');
INSERT INTO "PERSON" VALUES(494,'Steven Goodwin');
INSERT INTO "PERSON" VALUES(525,'Paul Adams');
INSERT INTO "PERSON" VALUES(531,'Marcel Offermans');
INSERT INTO "PERSON" VALUES(558,'Vincent Untz');
INSERT INTO "PERSON" VALUES(560,'Deepak Bhole');
INSERT INTO "PERSON" VALUES(562,'Karl Helgason');
INSERT INTO "PERSON" VALUES(567,'Remi Forax');
INSERT INTO "PERSON" VALUES(577,'Luca Foppiano');
INSERT INTO "PERSON" VALUES(586,'Remko Tronçon');
INSERT INTO "PERSON" VALUES(588,'Jack Moffitt');
INSERT INTO "PERSON" VALUES(589,'Simon Tennant');
INSERT INTO "PERSON" VALUES(593,'Wim Leers');
INSERT INTO "PERSON" VALUES(607,'Bernard Grymonpon');
INSERT INTO "PERSON" VALUES(616,'Peter Eisentraut');
INSERT INTO "PERSON" VALUES(618,'Sune Vuorela');
INSERT INTO "PERSON" VALUES(621,'Eike Rathke');
INSERT INTO "PERSON" VALUES(629,'Robert Schwebel');
INSERT INTO "PERSON" VALUES(631,'Andreas Scherbaum');
INSERT INTO "PERSON" VALUES(632,'Marc Balmer');
INSERT INTO "PERSON" VALUES(633,'Ed Schouten');
INSERT INTO "PERSON" VALUES(635,'Dave Page');
INSERT INTO "PERSON" VALUES(638,'Koen Martens');
INSERT INTO "PERSON" VALUES(640,'Mike Connor');
INSERT INTO "PERSON" VALUES(645,'Paul Rouget');
INSERT INTO "PERSON" VALUES(658,'David Fifield');
INSERT INTO "PERSON" VALUES(660,'Isabel Drost');
INSERT INTO "PERSON" VALUES(661,'Elena Reshetova');
INSERT INTO "PERSON" VALUES(662,'Wim Remes');
INSERT INTO "PERSON" VALUES(663,'David Recordon');
INSERT INTO "PERSON" VALUES(664,'Richard Clayton');
INSERT INTO "PERSON" VALUES(665,'Brooks Davis');
INSERT INTO "PERSON" VALUES(666,'Greg Kroah-Hartman');
INSERT INTO "PERSON" VALUES(668,'Lindsay Holmwood');
INSERT INTO "PERSON" VALUES(670,'Bernard Li');
INSERT INTO "PERSON" VALUES(671,'Benoît Chesneau');
INSERT INTO "PERSON" VALUES(672,'Sergey Petrunya');
INSERT INTO "PERSON" VALUES(673,'Dylan Schiemann');
INSERT INTO "PERSON" VALUES(674,'Christoph Pojer');
INSERT INTO "PERSON" VALUES(675,'Evan Prodromou');
INSERT INTO "PERSON" VALUES(676,'Sacha Storz');
INSERT INTO "PERSON" VALUES(677,'Adrian Bowyer');
INSERT INTO "PERSON" VALUES(678,'Florian Schiessl');
INSERT INTO "PERSON" VALUES(679,'Xavier DUTOIT');
INSERT INTO "PERSON" VALUES(680,'Steven Lamerton');
INSERT INTO "PERSON" VALUES(682,'Sylvain Beucler');
INSERT INTO "PERSON" VALUES(683,'David Reyes Samblas Martinez');
INSERT INTO "PERSON" VALUES(684,'Guus Sliepen');
INSERT INTO "PERSON" VALUES(686,'Daniel-Constantin Mierla');
INSERT INTO "PERSON" VALUES(687,'Andreas Schneider');
INSERT INTO "PERSON" VALUES(688,'Amanda Waite');
INSERT INTO "PERSON" VALUES(689,'Matthieu Fertre');
INSERT INTO "PERSON" VALUES(690,'Solomon Hykes');
INSERT INTO "PERSON" VALUES(691,'Koen Deforche');
INSERT INTO "PERSON" VALUES(692,'Andrew Lewman');
INSERT INTO "PERSON" VALUES(693,'Ian Grigg');
INSERT INTO "PERSON" VALUES(694,'Giuseppe Maxia');
INSERT INTO "PERSON" VALUES(695,'Salve Nilsen');
INSERT INTO "PERSON" VALUES(696,'Oscar Puyal');
INSERT INTO "PERSON" VALUES(697,'Gabor Szabo');
INSERT INTO "PERSON" VALUES(698,'Julia Lawall');
INSERT INTO "PERSON" VALUES(699,'Christophe Van Ginneken');
INSERT INTO "PERSON" VALUES(700,'Johan Euphrosine');
INSERT INTO "PERSON" VALUES(702,'Mark Michelson');
INSERT INTO "PERSON" VALUES(703,'clement Game');
INSERT INTO "PERSON" VALUES(704,'Patrick Ohly');
INSERT INTO "PERSON" VALUES(705,'Benjamin Zores');
INSERT INTO "PERSON" VALUES(706,'Rubin Simons');
INSERT INTO "PERSON" VALUES(707,'Dieter Plaetinck');
INSERT INTO "PERSON" VALUES(708,'Fabien Pinckaers');
INSERT INTO "PERSON" VALUES(709,'Andrew Tanenbaum');
INSERT INTO "PERSON" VALUES(710,'Dirk Ooms');
INSERT INTO "PERSON" VALUES(711,'Erwan Loisant');
INSERT INTO "PERSON" VALUES(713,'Marc Delisle');
INSERT INTO "PERSON" VALUES(714,'Piotr Biel');
INSERT INTO "PERSON" VALUES(715,'Kristian Nielsen');
INSERT INTO "PERSON" VALUES(716,'David Axmark');
INSERT INTO "PERSON" VALUES(717,'Seppo Jaakola');
INSERT INTO "PERSON" VALUES(718,'Frédéric Descamps');
INSERT INTO "PERSON" VALUES(719,'Geert Vanderkelen');
INSERT INTO "PERSON" VALUES(720,'Vladimir Kolesnikov');
INSERT INTO "PERSON" VALUES(721,'Ronald Bradford');
INSERT INTO "PERSON" VALUES(722,'Stéphane Combaudon');
INSERT INTO "PERSON" VALUES(723,'Roland Bouman');
INSERT INTO "PERSON" VALUES(725,'Aleix Pol');
INSERT INTO "PERSON" VALUES(726,'Nick Papoylias');
INSERT INTO "PERSON" VALUES(728,'Steve Frécinaux');
INSERT INTO "PERSON" VALUES(729,'Richard Hughes');
INSERT INTO "PERSON" VALUES(730,'Tobias Mueller');
INSERT INTO "PERSON" VALUES(731,'Joaquim Rocha');
INSERT INTO "PERSON" VALUES(732,'Lionel Dricot');
INSERT INTO "PERSON" VALUES(736,'François Revol');
INSERT INTO "PERSON" VALUES(737,'Thomas Doerfler');
INSERT INTO "PERSON" VALUES(738,'Olivier Coursière');
INSERT INTO "PERSON" VALUES(739,'Olaf Buddenhagen');
INSERT INTO "PERSON" VALUES(740,'Uros Nedic');
INSERT INTO "PERSON" VALUES(741,'Dirk Vogt');
INSERT INTO "PERSON" VALUES(742,'Niels Sascha Reedijk');
INSERT INTO "PERSON" VALUES(743,'Delphine Lebédel');
INSERT INTO "PERSON" VALUES(745,'Florian Effenberger');
INSERT INTO "PERSON" VALUES(746,'Henrik Skupin');
INSERT INTO "PERSON" VALUES(747,'Mitchell Baker');
INSERT INTO "PERSON" VALUES(748,'Bogomil Shopov');
INSERT INTO "PERSON" VALUES(749,'Kadir Topal');
INSERT INTO "PERSON" VALUES(750,'Carsten Driesner');
INSERT INTO "PERSON" VALUES(751,'Bjoern Michaelsen');
INSERT INTO "PERSON" VALUES(752,'Bart Hanssens');
INSERT INTO "PERSON" VALUES(753,'Svante Schubert');
INSERT INTO "PERSON" VALUES(754,'Luis Belmar-Letelier');
INSERT INTO "PERSON" VALUES(755,'Ulrich Schroeter');
INSERT INTO "PERSON" VALUES(756,'Andrew Savory');
INSERT INTO "PERSON" VALUES(757,'Bruno Cornec');
INSERT INTO "PERSON" VALUES(758,'Guillaume Rousse');
INSERT INTO "PERSON" VALUES(759,'Stefano Zacchiroli');
INSERT INTO "PERSON" VALUES(760,'John Thomson');
INSERT INTO "PERSON" VALUES(761,'Anne Nicolas');
INSERT INTO "PERSON" VALUES(762,'Armel Kermovant');
INSERT INTO "PERSON" VALUES(763,'Sandro Mathys');
INSERT INTO "PERSON" VALUES(764,'Marcus Moeller');
INSERT INTO "PERSON" VALUES(766,'Dominique Dumont');
INSERT INTO "PERSON" VALUES(767,'Nicolas Pierron');
INSERT INTO "PERSON" VALUES(768,'Pavol Rusnak');
INSERT INTO "PERSON" VALUES(769,'Christopher Hofmann');
INSERT INTO "PERSON" VALUES(770,'Harald Hoyer');
INSERT INTO "PERSON" VALUES(771,'Bertrand Rousseau');
INSERT INTO "PERSON" VALUES(772,'Rob Taylor');
INSERT INTO "PERSON" VALUES(773,'Ruben Vermeersch');
INSERT INTO "PERSON" VALUES(774,'Stéphane Delcroix');
INSERT INTO "PERSON" VALUES(775,'Lluis Sanchez Gual');
INSERT INTO "PERSON" VALUES(776,'Ivan Porto Carrero');
INSERT INTO "PERSON" VALUES(777,'Alan McGovern');
INSERT INTO "PERSON" VALUES(778,'Jérémie Laval');
INSERT INTO "PERSON" VALUES(779,'Jim Purbrick');
INSERT INTO "PERSON" VALUES(780,'Andreia Gaita');
INSERT INTO "PERSON" VALUES(781,'Jo Shields');
INSERT INTO "PERSON" VALUES(782,'Mirco Bauer');
INSERT INTO "PERSON" VALUES(783,'Steven Noels');
INSERT INTO "PERSON" VALUES(784,'Tim Anglade');
INSERT INTO "PERSON" VALUES(785,'Kristina Chodorow');
INSERT INTO "PERSON" VALUES(786,'Lars George');
INSERT INTO "PERSON" VALUES(787,'Eric Evans');
INSERT INTO "PERSON" VALUES(788,'Benoit Chesneau');
INSERT INTO "PERSON" VALUES(789,'Rob Tweed');
INSERT INTO "PERSON" VALUES(790,'George James');
INSERT INTO "PERSON" VALUES(791,'Evert Arckens');
INSERT INTO "PERSON" VALUES(792,'Fred Kiefer');
INSERT INTO "PERSON" VALUES(793,'David Chisnall');
INSERT INTO "PERSON" VALUES(794,'Matt Barringer');
INSERT INTO "PERSON" VALUES(795,'Peter Stuge');
INSERT INTO "PERSON" VALUES(796,'Rudolf Marek');
INSERT INTO "PERSON" VALUES(797,'Carl-Daniel Hailfinger');
INSERT INTO "PERSON" VALUES(798,'Luc Verhaegen');
INSERT INTO "PERSON" VALUES(799,'Mikhail Gusarov');
INSERT INTO "PERSON" VALUES(800,'Matthias Vandermaesen');
INSERT INTO "PERSON" VALUES(801,'Simon Elliot');
INSERT INTO "PERSON" VALUES(802,'Roel de Meester');
INSERT INTO "PERSON" VALUES(803,'Károly Négyesi');
INSERT INTO "PERSON" VALUES(804,'Dieter de Waele');
INSERT INTO "PERSON" VALUES(805,'Florian Lorétan');
INSERT INTO "PERSON" VALUES(806,'Boris Doesborg');
INSERT INTO "PERSON" VALUES(807,'Edward Nevill');
INSERT INTO "PERSON" VALUES(808,'Roberto Guido');
INSERT INTO "PERSON" VALUES(809,'Falko Menge');
INSERT INTO "PERSON" VALUES(810,'Mark Proctor');
INSERT INTO "PERSON" VALUES(811,'Sabri Skhiri');
INSERT INTO "PERSON" VALUES(812,'Yoeri Roels');
INSERT INTO "PERSON" VALUES(813,'Heikko Rupp');
INSERT INTO "PERSON" VALUES(814,'Philip Tellis');
INSERT INTO "PERSON" VALUES(815,'Marc Lainez');
INSERT INTO "PERSON" VALUES(816,'Bert Meerman');
INSERT INTO "PERSON" VALUES(817,'Tuomas Koski');
INSERT INTO "PERSON" VALUES(818,'Laurent Eschenauer');
INSERT INTO "PERSON" VALUES(819,'Alard Weisscher');
INSERT INTO "PERSON" VALUES(820,'Tiago Camargo');
INSERT INTO "PERSON" VALUES(821,'Sjoerd Simons');
INSERT INTO "PERSON" VALUES(822,'François Stephany');
INSERT INTO "PERSON" VALUES(823,'Christopher Blizzard');
INSERT INTO "PERSON" VALUES(824,'Alina Mierlus');
INSERT INTO "PERSON" VALUES(825,'Patrick Welche');
INSERT INTO "PERSON" VALUES(826,'Sascha Hauer');
INSERT INTO "PERSON" VALUES(827,'Peter Korsgaard');
INSERT INTO "PERSON" VALUES(828,'Yann E. Morin');
INSERT INTO "PERSON" VALUES(829,'Adrien Ampelas');
INSERT INTO "PERSON" VALUES(831,'Daniel Stenberg');
INSERT INTO "PERSON" VALUES(832,'Bart Van Der Meerssche');
INSERT INTO "PERSON" VALUES(833,'Víctor Manuel Jáquez Leal');
INSERT INTO "PERSON" VALUES(834,'Kuo-Kun Tseng');
INSERT INTO "PERSON" VALUES(835,'Wolfgang De Meuter');
INSERT INTO "PERSON" VALUES(836,'Laurent Pinchart');
INSERT INTO "PERSON" VALUES(837,'Roberto Jacinto');
INSERT INTO "PERSON" VALUES(838,'Friedger Müffke');
INSERT INTO "PERSON" VALUES(839,'Aki Niemi');
INSERT INTO "PERSON" VALUES(841,'Bas Wijnen');
INSERT INTO "PERSON" VALUES(842,'Jon Phillips');
INSERT INTO "PERSON" VALUES(843,'Mirko Lindner');
INSERT INTO "PERSON" VALUES(845,'Daniel Wehner');
INSERT INTO "PERSON" VALUES(846,'Kristof van Tomme');
INSERT INTO "PERSON" VALUES(847,'Axel Beckert');
INSERT INTO "PERSON" VALUES(848,'Giorgos Keramidas');
INSERT INTO "PERSON" VALUES(850,'Stijn Beauprez');
INSERT INTO "PERSON" VALUES(851,'Niels Heyvaert');
INSERT INTO "PERSON" VALUES(852,'Thomas Zimmermann');
INSERT INTO "PERSON" VALUES(853,'David Wagner');
INSERT INTO "PERSON" VALUES(854,'Manuel de la Peña');
INSERT INTO "PERSON" VALUES(856,'Lars Sonchocky-Helldorf');
CREATE TABLE EVENT ( xid_conference INTEGER  NOT NULL
    , id INTEGER NOT NULL
    , start INTEGER NOT NULL
    , duration INTEGER NOT NULL
    , xid_track INTEGER NOT NULL REFERENCES TRACK(id)
    , type VARCHAR
    , language VARCHAR
    , tag VARCHAR
    , title VARCHAR NOT NULL
    , subtitle VARCHAR
    , abstract VARCHAR
    , description VARCHAR
    , favourite INTEGER DEFAULT 0
    , alarm INTEGER DEFAULT 0
    , PRIMARY KEY (xid_conference ,id)
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_track) REFERENCES TRACK(id));
INSERT INTO "EVENT" VALUES(1,819,1265446800,2700,1,'Podium','English','welcome','Welcome','','FOSDEM Opening Talk','FOSDEM was started under the name OSDEM (Open Source Developers of Europe Meeting) by Raphael Bauduin. Raphael says that, since he felt he lacked the brains to properly contribute to the open source community, he wanted to contribute by launching a European event in Brussels. It was an immediate success, with speakers coming from all over.

The FOSDEM conference is coming to its tenth birthday. We will quickly go over the history and present.',0,0);
INSERT INTO "EVENT" VALUES(1,803,1265449500,2700,1,'Podium','English','promoting','Promoting Open Source Methods at a Large Company','','This talk will
cover Aerosource, our project to bring open source development tools
and methods to internal developers.','At the Aerospace corporation our approximately 2500 engineers developer
a lot of software in the course of doing their jobs.  This talk will
cover Aerosource, our project to bring open source development tools
and methods to internal developers.  Aerosource is a project hosting
environment built on open source tools including Apache, FreeBSD,
PostgreSQL, Python, and Trac.  We will share our experiences and
successes at promoting open source methods in a traditionally closed
environment.',0,0);
INSERT INTO "EVENT" VALUES(1,802,1265453100,2700,1,'Podium','English','eviloninternet','Evil on the Internet','','This talk will show
you live examples of these sites, explain how they work, and tell you
what we currently know about the criminals who operate them.','There''s a lot of evil things on the Internet if you know where to look
for them. Phishing websites collect banking credentials; mule
recruitment websites entice people into money laundering; fake escrow
sites defraud the winners of online auctions; fake banks hold the cash
for fake African dictators; and there are even Ponzi scheme websites
where (almost) everyone knows that they''re a scam.  This talk will show
you live examples of these sites, explain how they work, and tell you
what we currently know about the criminals who operate them.',0,0);
INSERT INTO "EVENT" VALUES(1,809,1265461200,2700,2,'Podium','English','systemtap','What is my system doing - Full System Observability with SystemTap','','SystemTap an application that observes your system on multiple levels, from kernel, libraries, applications, java to database transactions. SystemTap is a new player in the monitoring world!:t','Ever wondered what your system is really doing? Even if your whole system consists of Free Software you might still be scratching your head about what is really going on. Reading all the sources or staring at a core dump after the fact only gets you that far. You have to observe your system while it is running. Luckily the last few years there has been lots of improvements in GNU/Linux around how to monitor, trace, profile and debug your system. Kernel ftrace, pref, tracepoints, better debuginfo, application and library probe points, tapsets and compatibility with dtrace. Systemtap can take advantage of it all and provides a powerful way to get full system observability.

Want to dive deep into applications, java processes or the linux kernel without needing to stop or interrupt anything? SystemTap is the tool of choice for complex tasks that may require live analysis, programmable on-line response, and whole-system symbolic access. SystemTap can also handle simple tracing jobs. Learn how to setup SystemTap, what ready to run scripts there are, and how to tailor your probes to specific applications or kernel usage patterns.

SystemTap can observe on multiple levels, from kernel, libraries, applications, java to database transactions. To help users to get a better view what an application is doing you can add tapsets and static markers. And such markers can be made compatible with dtrace (to make your solaris hacker friends happy). There are already lots of packages that provide such high level observability, Postgresql, Java hotspot, Xorg, Python, Firefox, etc. Learn how to rapid prototype observability of your application through tapsets with function and statement probes (on any existing binary) and how to add high-level (zero-overhead) markers to your package sources that tell users about everything important, passes, transactions, service starting/stopping, etc.',0,0);
INSERT INTO "EVENT" VALUES(1,810,1265464800,2700,2,'Podium','English','ganglia','Ganglia: 10 years of monitoring clusters and grids','','During the talk Bernard will give an overview of Ganglia''s strong points and it''s technical architecture.','This talk will start off with a brief overview of the early beginnings of the project and how it has become the de facto standard for monitoring clusters and grids. The talk will then dive into the technical architecture of the system, discuss scalability issues, challenges ahead in adapting the software for cloud environments and other future developments. If you work with a lot of computers, then this talk is for you.

Ganglia is a scalable system performance monitoring software started by Matt Massie in 1999 while he was at the University of California, Berkeley working on the Millennium Project.  Since the inception of the project, it has seen 40+ releases and 299,208 total downloads recorded by SourceForge.net. Ganglia is simple to install and use and is available on most UNIX platforms. 30+ system metrics such as CPU load, memory usage, network traffic are collected by default and can be further extended via a command line metric reporting tool or pluggable modules written in C or Python. Ganglia is being used extensively all over the world by organizations large and small.',0,0);
INSERT INTO "EVENT" VALUES(1,808,1265468400,2700,2,'Podium','English','flapjack','Starting the sysadmin tools renaissance: Flapjack + cucumber-nagios','','Monitoring software is ripe for a renaissance. Now is the time to for building new tools and rethinking our problems. 
Leading the charge are two projects: cucumber-nagios, and Flapjack.','A systems administrator''s role in today''s technology landscape has never been so important. It''s our responsibility to manage provisioning and maintenance of massive infrastructures, to anticipate ahead of time when capacity must be grown or shrunk, and increasingly, to make sure our applications scale. 

While developer tools have improved tremendously, we sysadmins are still living in the dark ages, other than a few shining beacons of hope such as Puppet. We''re still trying to make Nagios scale. We''re still writing the same old monitoring checks. Getting statistics out of our applications is tedious and difficult, but increasingly important to scaling. 

cucumber-nagios lets you describe how a website should work in natural language, and outputs whether it does in the Nagios plugin format. It includes a standard library of website interactions, so you don''t have to rewrite the same Nagios checks over and over. 

cucumber-nagios can also be used to check SSH logins, filesystem interactions, mail delivery, and Asterisk dialplans. By lowering the barrier of entry to writing fully featured checks, there''s no reason not to start testing all of your infrastructure. But as you start adding more checks to your monitoring system you''re going to notice slowdowns and reliability problems - enter Flapjack

Flapjack is a scalable and distributed monitoring system. It natively talks the Nagios plugin format (so you can use all your existing Nagios checks), and can easily be scaled from 1 server to 1000. 

Flapjack breaks the monitoring lifecycle into several distinct chunks: workers that execute checks, notifiers that notify when checks fail, and an admin interface to manage checks and events. 

By breaking the monitoring lifecycle up, it becomes incredibly easy to scale your monitoring system with your infrastructure. Need to monitor more servers? Just add another server to the pool of workers. Need to take down your workers for maintenance? Just spin up another pool, and turn off the old one.',0,0);
INSERT INTO "EVENT" VALUES(1,799,1265461200,2700,3,'Podium','English','maemo','Maemo 6 security framework, making happy DRM business and freedom lovers with the same device','','The presentation will cover the Maemo Platform Security Architecture in more details, providing a deeper technical view on its components and their interaction.','The purpose of the Platform Security in the Maemo 6 platform is to protect the owner of a Maemo-powered device from getting her personal, private data and passwords from being stolen and used for malicious purposes, to prevent a malware from misusing a device and incurring costs on user, to prevent a user from accidentally breaking the device and to make the platform meet the requirements set by such third party software that requires a safe execution environment.

The presentation will cover the Maemo Platform Security Architecture in more details, providing a deeper technical view on its components and their interaction.',0,0);
INSERT INTO "EVENT" VALUES(1,797,1265464800,2700,3,'Podium','English','nmap','The Nmap scripting engine','','The Nmap Scripting Engine extends the results of an Nmap port scan. It
combines the Lua programming language, a library of network functions,
and the results provided by other parts of Nmap to give more information
about network hosts and their open ports.','There are standard scripts that grab SSH host keys or SSL certificates, discover the remote date
and time, check for weak passwords and unpatched vulnerabilites, and
much more.

The talk will explain how the scripting engine fits in with Nmap''s other
functions, the structure of a script, and how to modify a script or
write your own. We''ll see how the scripting engine can benefit casual
users, researchers, and security auditors. Finally there will be a brief
overview of what''s new in Nmap and its associated tools for the benefit
of casual users.',0,0);
INSERT INTO "EVENT" VALUES(1,800,1265468400,2700,3,'Podium','English','ossec','OSSEC','','Expect an overview of the basic architecture as well as practical examples of how to customize OSSEC to manage logging from your infrastructure and applications.','Log management, Intrusion detection/prevention and event correlation is a challenge we have been facing for decades.  Most of us have been able to ignore it but with developments in regulatory compliance (PCI-DSS, HIPAA, SOX, ISO27K, ...) companies are required to investigate solutions.  
In this talk we will firstly touch upon the
problems that will be faced during such a project and how log management will look in the future (new standards are on their way).   After this boring introduction to
the magical world that is log management and intrusion detection we will delve into the solution that is presented with OSSEC.  While labeled as a Host-based Intrusion
Detection System (HIDS), OSSEC provides you with a complete arsenal of functionalities that allow you to build a log management solution which will translate
the most cryptic log message into a clear and actionable alert.  Expect an overview of the basic architecture as well as practical examples of how to customize OSSEC to manage logging from your infrastructure and applications.',0,0);
INSERT INTO "EVENT" VALUES(1,832,1265457600,900,4,'Lightning-Talk','English','fosdem','FOSDEM: Lightning Opening Talk','','The main goal is to buffer the time between the opening of the room, and the first real lightning talk.

If time permits, there will be a lightning talk about the lightning talks: with statistics about the proposals and acceptances, and the story of how these lightning talks are organized. Extra time can be filled with questions related to the organisation of the FOSDEM conference at large.','The FOSDEM Lightning Talks are organized by Mattias ''Tias'' Guns since 2007. The lightning talks allow projects that do not fit in a developer room to present themselves to the large developer audience at FOSDEM.

Lightning Talks can be described as the 15 minutes of fame for all free or open source projects. During exactly 15 minutes, one person gets to present the project or any aspect of it. All the lightning talks happen in a large room that can host up to 300 people.',0,0);
INSERT INTO "EVENT" VALUES(1,833,1265458500,900,4,'Lightning-Talk','English','limux','LiMux: 5 years on the way to free software in Munich','','The talk gives a brief general view on the project''s political and technical background in Germany''s largest Municipality, shows the goals already achieved like the complete migration to OpenOffice.org and the city-wide use of the Open Document Format (ODF) and explains the steps for the next two years, the large-scale migration to the linux client.','Munich''s LiMux project aims at the use of free software and open standards on most of the 14,000 PCs of the Municipality''s administration. Challenges are the integration of the Debian GNU/Linux client, the availability of (proprietary) business applications for this linux client and the migration to OpenOffice.org.',0,0);
INSERT INTO "EVENT" VALUES(1,834,1265459400,900,4,'Lightning-Talk','English','civicrm','CiviCRM: Common goals of FOSS and Not For Profit Organisations','','CiviCRM support the work of NGOs on advocacy and better communication with their members and the general public. It allows to handle newsletters, receive donations, manage the membership and help organising events, all sharing the same contact database, and offering a 360 view of their contacts.

But beside helping the NGOs to work better with an efficient software, there is also a common set of values about sharing, openness, transparency and freedom that are should be better promoted by FOSS promoters and better understood by NGOs.

I will present how CiviCRM can help the civil society, and how to highlight these shared values while introducing FOSS to the civil society.

All that in 15 minutes.','CiviCRM is an open source and freely downloadable constituent relationship management solution. It iss web-based, open source, internationalized, and designed specifically to meet the needs of advocacy, non-profit and non-governmental groups. Integration with both Drupal and Joomla! content management systems gives you the tools to connect, communicate and activate your supporters and constituents.',0,0);
INSERT INTO "EVENT" VALUES(1,835,1265461200,900,4,'Lightning-Talk','English','portableapps','PortableApps.com: The PortableApps.com Platform, an Introduction and Overview','','This lightning talk will give a brief introduction and general overview of the PortableApps.com Platform. In particular it will look at how the platform is structured, why you should develop for it and how to become compatible with it.','PortableApps.com is the world''s most popular portable software solution allowing you to take your favourite software with you. A fully open source and free platform, it works on any portable storage device (USB flash drive, iPod, memory card, portable hard drive, etc).',0,0);
INSERT INTO "EVENT" VALUES(1,864,1265462100,900,4,'Lightning-Talk','English','openpcf','OpenPCF: An Open Provisioning and Control Framework','','Originally, I wanted to do a talk which actually demonstrates the automated setup of a RHEL 4 or 5, Debian 4 or 5 or NetBSD 4 or 5 system live, and using the resulting system to deploy new systems. However, I think 15 minutes would be a little tight for that. I want to talk about:

1: 5 minutes introduction: why openpcf
2: 5 minutes internals: how it works
3: 5 minutes results: what you can do with it','OpenPCF (which stands for Open Provisioning and Control Framework) is an open-source, automated system configuration tool. It can generate configurations for any service that runs on a posix-like platform. Services like DHCP, DNS, HTTP, LDAP and many more are supported.

OpenPCF aims to automate the often-times manual labour of configuring services on a computer system you''ve just setup. The ultimate goal is a system that sets up all services needed within a datacenter resulting in a computer system that can deploy (through tftp, dhcp, pxe, http, nfs, cifs) various operating systems.',0,0);
INSERT INTO "EVENT" VALUES(1,837,1265463000,900,4,'Lightning-Talk','English','gnu_savannah','GNU Savannah: 100% free software mass-hosting','','GNU Savannah helps thousands of teams to work collaboratively on free software and documentation.
We''ll present the software and hardware architecture, give an overview of the daily maintenance, and introduce the next-generation codebase of ''Savane'', the piece of software that binds it all together.','GNU Savannah is a hosting platform for free software projects, using free software technologies such as Git, Bzr, Mailman, OpenSSH, Apache...  It hosts > 3000 reviewed projects and is used by > 45K users.
The infrastructure relies on the Savane software project which is undergoing a full rewrite based on Python/Django.',0,0);
INSERT INTO "EVENT" VALUES(1,838,1265464800,900,4,'Lightning-Talk','English','qi_hardware','Qi Hardware''s Ben NanoNote: open to the bone device','','Introduction to Qi Hardware Ben NanoNote and possibilities a  Copyleft hardware device can bring to hardware design and software development','Qi Hardware is a project to build, use and recycle electronic devices around principles of self-organization, all documentation is under CCSA, including internal schematics , building processes, and of course software is GPL, but far beyond that we are trying to make all processes to use only FOSS tools, including design of hardware (kicad), production (testing software), management, marketing etc, etc
At the moment we are focusing on our first device, a mini computer called Ben NanoNote.',0,0);
INSERT INTO "EVENT" VALUES(1,839,1265465700,900,4,'Lightning-Talk','English','tinc','tinc: the difficulties of a peer-to-peer VPN on the hostile Internet','','Rather than configuring tunnels, a tinc VPN is more or less specified by its endpoints. The tinc daemons will automatically set up tunnels in order to create a full mesh network. The problem in today''s Internet is that many users are trapped behind NAT, and ISPs are known to drop ICMP packets, IP fragments, and/or UDP packets, making reliable connections between peers difficult.  Another problem is how to manage authentication and authorization in a fully decentralized, but user-friendly way.  In this talk I will look at solutions already implemented in tinc and other VPN software, and I look at future work to solve the remaining problems.','tinc is a Virtual Private Network (VPN) daemon that automatically tries to create a full mesh network between peers. It can route IPv4 and IPv6 packets, or switch any type of Ethernet packet to create a virtual LAN. It can tunnel over IPv4 and IPv6, and runs on Linux, *BSD, Solaris, MacOS/X and Windows.',0,0);
INSERT INTO "EVENT" VALUES(1,840,1265466600,900,4,'Lightning-Talk','English','beernet','Beernet: Building peer-to-peer systems with transactional replicated storage','','We will very briefly introduce Beernet''s architecture describing the peer-to-peer network topology, the distributed hash table, and the transactional layer for replicated storage (called Trappist). We will also describe Beernet''s API to create peers, exchange information between them, and to store and retrieve data from them. We will finally describe some applications built on top of Beernet, such as a small wiki, a collaborative drawing tool, and a web-base recommendation system.','Beernet is a library to build distributed systems as peer-to-peer networks. It provides replicated storage with distributed transactions, which are highly robust because they do not rely on a centralized point of control. Beernet can be used to develop synchronous and asynchronous collaborative applications. We have used it to build a decentralized wiki, a collaborative drawing application with gPhone clients, and a web-base recommendation system.

Beernet stands for pbeer-to-pbeer network, where words peer and beer are mixed to emphasise the fact that this is peer-to-peer built on top of a relaxed-ring topology (beers are a known mean to achieve relaxation). The relaxed-ring provides a distributed hash table (DHT) with no central point of control and without relying on transitive connectivity between peers.',0,0);
INSERT INTO "EVENT" VALUES(1,841,1265468400,900,4,'Lightning-Talk','English','sip_communicator','SIP Communicator: Skype-like conf calls with SIP Communicator','','Most of us have probably seen at one point or another someone using Skype for a conference call. We all know how well it works and how good it looks. In the SIP Communicator project, we have recently implemented support for a similar feature. In addition to mixing audio streams from all participants and then sending it back to them, we also distribute member information and audio level analysis to all members. We even support distributed conferences where mixing resources are provided by several different clients, and yet, all members get to the same view of the call and who''s in it. 

We believe that the various difficulties that we''ve faced along the way would be interesting to people working in the field of real-time communication and would therefore love to present them. The talk would be technical but would not require substantial technical background. In other words, if you are interested in VoIP then chances are you would like to see it.','SIP Communicator is an open source (LGPL) audio/video Internet phone and instant messenger. It includes support for advanced telephony features such as conference calls, call transfer, and video calls with SIP. Jabber calls with jingle are also on the way. IM wise the application supports some of the most popular protocols such as SIP, Jabber, AIM/ICQ, MSN, Yahoo! Messenger and others.',0,0);
INSERT INTO "EVENT" VALUES(1,842,1265469300,900,4,'Lightning-Talk','English','kamailio_sip_server','Kamailio (OpenSER) 3.0.0: redefinition of SIP server','','Kamailio (OpenSER) 3.0.0 release represents a big step forward for the SIP server, with many new features and enhancements. Along with ability to run SIP Express Router (SER) modules due to the new SIP-Router.org core framework, it brings asynchronous TCP, refurbished secure transport TLS and SCTP, new command line interface (cli), number portability and topology hiding support, memcached connector and internal dns caching system. The presentation will focus to highlight what Kamailio 3.0.0 can offer to build scalable VoIP platforms.','Kamailio (former OpenSER) is an Open Source SIP Server released under GPL, able to handle thousands of call setups per second. Among features: asynchronous TCP, UDP and SCTP, secure communication via TLS for VoIP (voice, video), SIMPLE instant messaging and presence, ENUM, least cost routing, load balancing, routing fail-over, accounting, authentication and authorization against MySQL, Postgres, Oracle, Radius, LDAP, XMLRPC control interface, SNMP monitoring. It can be used to build large VoIP servicing platforms or to scale up SIP-to-PSTN gateways, PBX systems or media servers like Asterisk, FreeSWITCH or SEMS.',0,0);
INSERT INTO "EVENT" VALUES(1,843,1265470200,900,4,'Lightning-Talk','English','asterisk','asterisk: An introduction to Asterisk Development','','A brief introduction to the tools used in Asterisk development, as well as the structure of the program. Information regarding how to submit new features and bug reports will be included as well.','Asterisk is an open source telephony platform, commonly used to implement PBX''s.',0,0);
INSERT INTO "EVENT" VALUES(1,844,1265472000,900,4,'Lightning-Talk','English','csync','csync: Roaming Home Directories','','This talk will be about a file synchronizer designed for the normal user. I will tell you how it and works and how you can use it to synchronize your music collection or set it up for Roaming Home Directories.','csync is a lightweight utility to synchronize files between two directories on a system or between multiple systems.

It synchronizes bidirectionally and allows the user to keep two copies of files and directories in sync. csync uses widely adopted protocols, such as smb or sftp, so that there is no need for a server component. It is a user-level program which means you don''t need to be a superuser or administrator.

Together with a Pluggable Authentication Module (PAM), the intent is to provide Roaming Home Directories for Linux.',0,0);
INSERT INTO "EVENT" VALUES(1,845,1265472900,900,4,'Lightning-Talk','English','faban','Faban: Developing benchmarks and workloads using Faban 1.0','','Faban 1.0 was released in November 2009, this lightning talk briefly looks at the features that Faban offers for developing benchmarks, infrastructure management services and load drivers and then will show what you need to do in order to write a driver from scratch.','Faban is a tool for developing and running benchmarks. Faban supports multi-tier server benchmarks (such as web/cache/database benchmarks) run across dozens of machines. It also supports developing and running a simple micro-benchmark targeting a single component (such as an ftp server.)',0,0);
INSERT INTO "EVENT" VALUES(1,846,1265473800,900,4,'Lightning-Talk','English','shadowcircle','shadowcircle:  a pentesting distribution alternative','','This talk would be about explaining what the shadowcircle project is: 

- why was it created. 
- what is the philosophy behind this project.
- what are you concretely able to do with the integrated tools.
- why is it better than other similar solution (backtrack)
- Final words : we need contributors to side projects in order to replace some non FOS software.

a Demo would also be performed : a vulnerabilities check on remote host ( implies 2 pc, provided by the speaker ) + exploit with specific payload.','shadowcircle is a free GNU/Linux Live CD distribution which was specially crafted for penetration testers. 

Forked from backtrack, this distribution aims to:

- Remove any peace of non free software that was initially the backtrack packages base, and replace them by FOS equivalents.
- Bring more documentation about the integrated tools. 
- Integrate cutting-edge security tools that are not yet available in similar distributions.',0,0);
INSERT INTO "EVENT" VALUES(1,847,1265475600,900,4,'Lightning-Talk','English','syncevolution','SyncEvolution: From the SyncML Protocol to Free and Open Implementations','','Data synchronization is still mostly a missing piece in the free desktop
puzzle: solutions that are reliable and ready for the mythical Average
User just aren''t available. This talk presents the SyncML protocol,
introduces the Synthesis SyncML engine (developed since 2000, open sourced
2009) and outlines how SyncEvolution is used as the synchronization
solution in Moblin, GNOME and other Linux desktop systems - stay tuned for
more news about this.

SyncEvolution is meant to be a cross-platform solution, therefore this
talk would be suitable for the cross-desktop developer room.

Direct synchronization with other mobile devices is the main new feature
in the upcoming Moblin 1.0 release. It will be covered in this talk for
the first time.','SyncEvolution is a tool that synchronizes personal information management (PIM) data like contacts, calenders, tasks, and memos using the SyncML information synchronization standard. SyncEvolution compiled for GNOME''s Evolution supports all of these data items. Compiled for Nokia 770/800/810 Internet Tablets, Mac OS X and the iPhone (only 0.7), it supports synchronizing the system address book. The command-line tool ''syncevolution'' (compiled separately for each of these platforms) executes the synchronization. In addition, there is the GTK "sync-UI". The external Genesis is a graphical frontend for SyncEvolution written in PyGTK. The GUIs make SyncEvolution accessible without having to use a command line and provides graphical feedback of transaction results.

SyncEvolution was written to have a small, reliable solution for Evolution PIM data synchronization without reinventing the wheel. SyncML is the established industry standard and Funambol has kindly provided their source code under the GPL, so there was already an existing code base for client and server development. During SyncEvolution''s development special attention was paid to automated testing and coverage of corner cases of the SyncML, vCard and iCalendar standards to ensure that no data gets lost or mangled.

The focus right now is to deliver the best possible SyncML client for Moblin and Linux. With the switch to the Synthesis SyncML Engine it will be easier to also implement a server mode and direct device-to-device synchronization - this is already working in the 1.0 alpha release.',0,0);
INSERT INTO "EVENT" VALUES(1,848,1265476500,900,4,'Lightning-Talk','English','geexbox','GeeXboX: An Introduction to Enna Media Center','','Enna is GeeXboX''s next generation Media Center interface, built upon Enlightenment Foundation Libraries (EFL). It allows you to listen to your music files, watch your favorite movies, TV shows and photos across your network. It relies on libplayer multimedia A/V abstraction framework to control your preferred player and libvalhalla, a fast media scanner API that will grab metadata (covers, fan arts, song lyrics and so many more) from your multimedia contents.','GeeXboX is a free embedded Linux distribution which aims at turning your computer into a so called HTPC (Home Theater PC) or Media Center. The GeeXboX project features both a LiveCD distribution and a standalone media center application (Enna); the project developed also several libraries (libplayer, libvalhalla) to enhance the multimedia experience under GNU/Linux.',0,0);
INSERT INTO "EVENT" VALUES(1,865,1265478000,900,4,'Lightning-Talk','English','uzbl','Uzbl: A webbrowser which adheres to the unix philosophy','','I will describe how the design ideas and implementation of Uzbl are radically different from other (even "lightweight") browsers.  Why this is important and which advantages this brings for hackers and control freaks.  I will demonstrate how one can leverage these properties to integrate webbrowsing with other activities and vice versa, by using simple scripts and tools.','Uzbl is:
* uzbl-core: a small program providing a UI to interact with webpages, a means to report events and send commands
* uzbl-browser: a complete browser implementation based on uzbl-core and various scripts providing commonly used features.
* many more scripts providing tabs, download managers etc',0,0);
INSERT INTO "EVENT" VALUES(1,1083,1265457600,1800,5,'Podium','English','emb_rich_mobile_ui','Rich Mobile UI Designs: do''s and don''t','','This presentation will give an overview of the available technologies/platforms with focus on the open source technologies and their adoption.','Also highlighting the open source projects supporting development for these platforms (with a focus on support for multiple platform development.',0,0);
INSERT INTO "EVENT" VALUES(1,1093,1265459400,1800,5,'Podium','English','emb_openintents','Openintents: Android intents mechanism','','The talk introduces the Android intents mechanism. It is an essential part of the design of the Android mobile operating
system that allows reuse and stimulates interoperability of apps.','From an open source perspective it also liberates the core functionality of the system, by making it possible to replace the native system applications. Extremely powerful if harnessed correctly, new Android developers ought to discover it early on, and hopefully embrace this unique feature en masse. For advanced aficionados, this talk will also briefly touch the related subjects of security and dependency management, an idea currently being discussed within OpenIntents.',0,0);
INSERT INTO "EVENT" VALUES(1,1082,1265461200,3600,5,'Podium','English','emb_best_practices','Embedded software development best practices','','Basing an embedded device on FOSS brings many advantages, not the least of which is complete control over the software stack and free reuse of existing high quality solutions. However, it also means having to deal with large amounts of code, mainly coming from external parties. Dealing with this can be a challenge for small embedded teams, used to smaller stacks developed in-house.','In this presentation, we take a step by step tour of good software development processes and how to use them to improve your organization. We emphasize embedded development and point out particular pitfalls to avoid.',0,0);
INSERT INTO "EVENT" VALUES(1,1084,1265464800,3600,5,'Podium','English','emb_limo','LiMo Platform and Mobile Linux','','LiMo are building an open mobile middleware platform upon the Linux kernel, drawing from the best of open source and using many common components found in GNOME Mobile.','The big challenge for mobile companies working with open source is how to be graceful in our interaction with upstream projects and how to ensure a reciprocal flow of innovation that benefits everyone.

This session will introduce the LiMo platform, talk about the challenges of building for mobile devices, and how we want to work with open source projects to make them more mobile in the future.',0,0);
INSERT INTO "EVENT" VALUES(1,1080,1265468400,3600,5,'Podium','English','emb_barebox','Barebox','','barebox is a new bootloader derived from the well-known U-Boot.','It aims for developers who like to use their linux-based development patterns also within the bootloader. This includes a device/driver-model, file system support using the usual commands (mount, ls, cp,...), modular design and scalability using Kconfig, shell-like scripting and alike. While being convenient, it is still easy to port to new boards or architectures. This talk will include a number of live-demonstrations and insights from the original creator of barebox. 

See [http://barebox.org/ http://barebox.org/] for more information.',0,0);
INSERT INTO "EVENT" VALUES(1,1086,1265472000,3600,5,'Podium','English','emb_flukso','Flukso: An Electricity metering application','','Flukso is an open source (HW & SW) web-based community metering application. Flukso allows you to accurately monitor and reduce your household electricity consumption via [http://www.flukso.net its website] and API.','This talk will focus on the embedded development of our 801.11g wireless sensor node called the Fluksometer. Fluksometer development went through several iterations. It evolved from a hacked-up Arduino - WRT54G prototype, via an Arduino Wee - Fonera in alpha to the custom sensor board - Abocom WAP2102 which we are now using in our beta trial.

This hybrid approach, connecting a custom sensor board to an off-the-shelf wifi router via UART, allowed us to develop a generic sensing platform that can be used for monitoring almost any physical unit, provided a suitable sensor can be found. We currently focus on measuring household electricity consumption and, in the near-future, photo-voltaic production. We will present our sensor node''s hardware (AVR and Atheros AR1217) and software (based on AVR-libc and OpenWRT 8.09) architecture and discuss its (dis)advantages and a lessons learned.',0,0);
INSERT INTO "EVENT" VALUES(1,1095,1265475600,3600,5,'Podium','English','emb_iris','Iris, a new capability-based microkernel OS','','Iris is a new capability-based microkernel operating system.','Being a microkernel system, it is easy to work on things which on other systems need kernel programming (and root priviledges).  Being a capability-based system, it allows transparent virtualization of everything.  This leads to improved security to such a degree, that the user can really trust the computer.  A capability-based system also allows easy monitoring of communication.  Another nice feature is that the user can swap target devices under a running program. I know we are in time to be very picky in the schedule, but should be cool if the speeches are made in different days',0,0);
INSERT INTO "EVENT" VALUES(1,934,1265458500,1800,6,'Podium','English','moz_europe','Mozilla Europe','','General Introduction followed by an update on the work of Mozilla in Europe.','',0,0);
INSERT INTO "EVENT" VALUES(1,935,1265460300,900,6,'Podium','English','moz_foundation','Mozilla Foundation','','Latest MoFo news and projects.','',0,0);
INSERT INTO "EVENT" VALUES(1,1074,1265461200,2700,6,'Podium','English','moz_floss','FLOSS: a key to self-determination in Internet life','','Mitchell will discuss how FLOSS is a force for building self-determination into our Internet lives.','',0,0);
INSERT INTO "EVENT" VALUES(1,1075,1265464800,1800,6,'Podium','English','moz_hackability','Hackability','','','',0,0);
INSERT INTO "EVENT" VALUES(1,939,1265466600,3600,6,'Podium','English','moz_html5','HTML 5','','','',0,0);
INSERT INTO "EVENT" VALUES(1,937,1265471100,3600,6,'Podium','English','moz_sync_weave','Sync/Weave','','How Weave and in particular sync is going to integrate with Firefox through 2010 and Firefox 4.','There will be some discussion on how add-on authors can integrate with Weave starting now, and directions being made to surface this data in the browser.',0,0);
INSERT INTO "EVENT" VALUES(1,828,1265461200,7200,7,'Other','English','typo3','TYPO3 exam session','','TYPO3 exam session','',0,0);
INSERT INTO "EVENT" VALUES(1,971,1265457600,2700,8,'Podium','English','dist_hermes','Hermes Message Dispatching','','Hermes is a message digesting and distribution system which is aimed to give back control to the user. Many already existing systems produce a lot of information for users, mostly by flooding with email. That was a very practical and quick solution in the past, but nowadays there are more elegant methods of notifying.','Hermes lets the user control, which information approaches him and how. It collects information from connected sources, manages user subscriptions to the various notification types and provides the user with a selection of the messages he wants to get, as mails, feeds or jabber messages and more.

This talk is an introduction to Hermes and the way the openSUSE project uses it for all kinds of notifications about the distribution.',0,0);
INSERT INTO "EVENT" VALUES(1,972,1265460300,2700,8,'Podium','English','dist_yast','YaST - Future Roadmap','','[http://docs.google.com/viewer?url=http://en.opensuse.org/images/b/b0/FOSDEM-2009-YaST.pdf At FOSDEM 2009, we presented an overview of YaST] related new developments and where we were heading.
In this talk we will review the progress made and present the features/ideas that have high priority for the next openSUSE release and areas where we are doing research that will eventually be features in future versions.','YaST is a powerful installation and system management tool for Linux environments. It is an open source project sponsored and actively developed by Novell, and part of openSUSE Linux since its inception. It has evolved a lot over time, providing single source modules that run in different user interfaces (QT4, GTK2, ncurses and web), as well as scripting language bindings.',0,0);
INSERT INTO "EVENT" VALUES(1,973,1265463000,2700,8,'Podium','English','dist_mirrorbrain','MirrorBrain','','MirrorBrain is a Download Redirector and Metalink Generator','MirrorBrain is an open source framework to run a content delivery network using mirror servers. It solves a challenge that many popular open source projects face - a flood of download requests, often magnitudes more than a single site could practically handle.

A central (and probably the most obvious) part is a "download redirector" which automatically redirects requests from web browsers or download programs to a mirror server near them.

Choosing a suitable mirror for a users request is the key, and MirrorBrain uses geolocation and global routing data to make a sensible choice, and achieve load-balancing for the mirrors at the same time. The used algorithm is both sophisticated and easy to control and tune. In addition, MirrorBrain monitors mirrors, scans them for files, generates mirror lists, and more.',0,0);
INSERT INTO "EVENT" VALUES(1,974,1265465700,3600,8,'Meeting','English','dist_infrastructure','Infrastructure round table','','Seeing that all distributions face the problem of maintaining their infrastructure (server landscape, keeping the services running, managing downtimes), this round table is an open discussion forum for infrastructure maintainers from all distributions and maybe other large projects which are running their own infrastructure.','After a short overview about the infrastructure issues a linux distribution can have, these issues can be discussed between the infrastructure maintainers of different distributions and other interested parties. Besides learning about how other people handle infrastructure issues, this round table should also be a means of getting to know the people behind the infrastructure of other distributions.

All infrastructure personnel attending FOSDEM is invited to join us in this round table.',0,0);
INSERT INTO "EVENT" VALUES(1,975,1265471100,2700,8,'Podium','English','dist_pkg_desc','Translations of package descriptions','','Easy software access should be considered as one of the key success for Linux distributions. One important consideration to ease the access to software is the quality and localization of software descriptions. At the moment each distribution has its own way to manage this using different processes, each one being more or less manual. This also requires a huge effort for localization teams since the amount of text to translate is important.','This session aims to start an effort of investigation on how this work can be mutualized between distributions: avoiding the duplicated work would certainly benefit everybody. This would also enable a focus on providing one user-friendly solution for localization teams to work on the translations. As a first step, the current processes in distributions have to be evaluated, in order to develop a good plan on how to best achieve a cross-distribution effort.',0,0);
INSERT INTO "EVENT" VALUES(1,961,1265473800,2700,8,'Podium','English','dist_gnome','Working with GNOME upstream','','This session is not a talk, but an interactive session. The goal of this session is to have the downstream and upstream people working on GNOME meet, joke, fight, laugh, cry and dance together. And after that, an open discussion will take place about all the topics that we feel we should discuss.','Potential topics include:
* what GNOME is not doing right for downstream, and how we could change this
* what GNOME is doing right compared to other projects, so we know this should not be changed ;-)
* forwarding downstream patches and bugs
* forwarding feedback from distribution users
* communicating important bugfixes to downstream
* how GNOME 3 will affect packagers',0,0);
INSERT INTO "EVENT" VALUES(1,977,1265476500,2700,8,'Podium','English','dist_spacewalk','Spacewalk: Linux Systems Lifecycle Management','','Brief introduction of the Spacewalk systems management solution with a short live demo.','Spacewalk is a free and open source lifecycle management which provides software management, provisioning and monitoring capabilities. The clean web interface allows viewing of systems and their software update status, as well as initiating actions like kickstarting systems or managing configuration files.
   
Spacewalk''s monitoring feature lets you view monitoring status for your systems alongside their software update status. Spacewalk also has virtualization capabilities to enable you to provision, control, manage, and monitor virtual Xen and KVM guests.',0,0);
INSERT INTO "EVENT" VALUES(1,957,1265461200,2700,8,'Podium','English','dist_maemo_council','The Maemo Community Council: a case-study in governance','','The co-operation between Nokia and non-Nokia members of the Maemo community has evolved radically over the lifetime of the project. Since its inception in 2008, the Maemo Community Council has become a key element of how the Maemo community co-operates with Nokia in setting priorities for the project. The council is elected by the Maemo Community, and represents the community''s interests to Nokia, and has a large say in the priorities of the maemo.org staff, a group of people paid by Nokia to work on the Maemo project.','This presentation will present the history and achievement of the council, with a view to identifying lessons which other vendor-led communities might be able to learn from the governance structure which has been put in place.',0,0);
INSERT INTO "EVENT" VALUES(1,958,1265463900,2700,8,'Podium','English','dist_fedora_governance','Fedora Governance','','In this talk, former Fedora Project Leader Max Spevack will discuss the governance and decision-making processes that exist within Fedora.','From individual contributors to special-interest-groups to the core projects that make up Fedora, this talk will explain not only how the Fedora Project is structured, but the underlying principles and goals of Fedora that have led it to have its current organizational structure.  The talk will also discuss some general ideas about governance and organization in volunteer-led communities -- both in Open Source, as well as other fields.',0,0);
INSERT INTO "EVENT" VALUES(1,959,1265466600,2700,8,'Podium','English','dist_hr_management','Distribution HR management','','The technical differences between distributions are often compared but big differences can also be found in how distributions manage their developer pool.','In this talk I will present how Gentoo manages their human resources and our views on what has worked and what hasn''t followed by a general discussion about distributions in general.',0,0);
INSERT INTO "EVENT" VALUES(1,1113,1265469300,1800,8,'Podium','English','dist_bootchart2','bootchart2','','A quick expose on boot time profiling tools, show-casing the slightly-less-lame: "bootchart2" - a new and improved boot time profiling tool, and other ways to speed things up."','Which of the seven+ ''readahead'' tools do you want, and why ? With a summary of recent fixes and wins in the area, and how to get involved with improving Linux boot performance.',0,0);
INSERT INTO "EVENT" VALUES(1,960,1265471100,2700,8,'Podium','English','dist_mobile_upstream','Mobile distributions and upstream challenges','','This talk will identify some of the key challenges from a mobile platform development perspective, and solicit feedback and discussion on how mobile platforms can be more distro-like and work better with upstream projects.','',0,0);
INSERT INTO "EVENT" VALUES(1,976,1265473800,2700,8,'Podium','English','dist_fedora_fr','Fedora-fr and upstream French communities','','Note that this session will be held in French !

Open Discussion around Fedora-Fr and FedoraProject.','* Who is Fedora-Fr organization ?
* Fedora-Fr Goals
* Fedora-Fr Website
* Fedora-Fr Events coverage in France in 2009 and 2010',0,0);
INSERT INTO "EVENT" VALUES(1,962,1265476500,2700,8,'Podium','English','dist_good_upstream','How to be a good upstream','','How upstreams run their projects determines how easy the projects are for packagers to package.','The aim of this coal is to introduce what kind things should be taken into account in order to make the life of  distributions easier.',0,0);
INSERT INTO "EVENT" VALUES(1,907,1265457600,900,9,'Other','English','gnome_welcome','Welcome to the GNOME devroom','','Welcome to the GNOME devroom','',0,0);
INSERT INTO "EVENT" VALUES(1,906,1265458500,2700,9,'Podium','English','gnome_bugsquad','GNOME Bugsquad','','This Bugsquad session will be about statistics and people.','While I''ll show, in what shape our bug database is, I''ll also explain, how to use the current infrastructure appropriately in order to manage our bugs. That includes how to use the bugtracker, the mailinglist and our IRC channel to successfully manage bugs.

We''ll have a Q&A session afterwards, where we explicitly want to introduce new triagers which will be part of the new bugsquad :)',0,0);
INSERT INTO "EVENT" VALUES(1,908,1265461200,3600,9,'Podium','English','gnome_color_manager','GNOME Color Manager','','GNOME Color Manager: exploring the user experience and integration points for a 100% color managed desktop','GNOME Color Manager is a new project intending to make color management in the GNOME desktop "just work". In this presentation I will quickly introduce why color management is required, and also the problems introducing a color management workflow. We will compare and contrast the frameworks commonly used in OSX and Windows 7. By discussing the integration points, we will be talking to application developers and platform maintainers in order to shape the future development of GNOME Color Manager. We will also spend some time exploring the intricacies of a color management framework best suitable for GNOME, and how GNOME Color Manager can start to provide this functionality.

There will be time left for questions and discussion. It is expected the audience will be moderately technically skilled, and possess a basic understanding of color management.',0,0);
INSERT INTO "EVENT" VALUES(1,904,1265464800,900,9,'Podium','English','gnome_multimedia_webkit','Multimedia in WebKitGTK+','','This talk would give an outline of the status of multimedia support in WebKitGTK+ thanks to GStreamer. How it was done until recently, what we improved and what we plan to work on during 2010.','',0,0);
INSERT INTO "EVENT" VALUES(1,909,1265465700,900,9,'Podium','English','gnome_guadec_2010','GUADEC 2010','','This year, GUADEC will take place in The Hague, The Netherlands on July 24th-30th. In this small presentation I will introduce the venue, and ask for help organising this edition of GUADEC.','',0,0);
INSERT INTO "EVENT" VALUES(1,905,1265467500,2700,9,'Podium','English','gnome_apps_plugins','Add plugins to your GNOME apps','','This talk will focus on libpeas, a lib-ification of the gedit plugin''s engine intended to allow adding support for plugins written in various languages (currently C, python, javascript) into gobject-based apps in a very simple and quick fashion.','',0,0);
INSERT INTO "EVENT" VALUES(1,903,1265470200,2700,9,'Podium','English','gnome_devtools','Gnome Development Tools','','Misha is a debug-oriented research I.D.E. developed at the Technical University of Crete and published under the GPLv3 license that introduces among other things: syntax-aware navigation, data-displaying and editing, reverse execution, debugging scripting and inter-language evaluation through the integration of its source-level debugger (gdb) with a full-fledged source parser, data visualisation tools and other free software technologies.','Misha, apart from introducing new debugging facilities (that we would also like to see and implement for Anjuta), is a great example of how new innovative widgets and programming interfaces can be implemented on top of the gtk+/pygtk libraries and the gnome platform.',0,0);
INSERT INTO "EVENT" VALUES(1,910,1265472900,2700,9,'Podium','English','gnome_ocrfeeder','OCRFeeder','','OCRFeeder is a document layout analysis and optical character recognition system that I wrote for my Master''s Thesis project.','Like it says on its website, given the images it will automatically outline its contents, distinguish between what''s graphics and text and perform OCR over the latter. It generates multiple formats being its main one ODT.

I think this is currently the most complete and user friendly OCR application for GNU/Linux out there and, of course, I wrote it to be used mainly with GNOME, featuring a GUI written in PyGTK and respecting, as far as I could, the GNOME User Interface Guidelines.

I would like to present how the application works on the inside, for example the page segmentation algorithm I created for it, etc. I think this would be interest for the GNOME community and general attendants of the GNOME Dev room at FOSDEM.',0,0);
INSERT INTO "EVENT" VALUES(1,911,1265475600,2700,9,'Podium','English','gnome_things','Getting Things GNOME!','','Getting Things GNOME! is a Python todo-list manager inspired by the Getting Things Done method.','GTG was first introduced during FOSDEM 2009. This talk will be a brief retrospective of one year of development and what we have learned from them. We will also cover the basis of GTG structure, have a brief look at the future and, if everybody is still not asleep, explain the first steps to contribute to GTG because, in GTG, fixing a bug is often easier than writing the bug report.',0,0);
INSERT INTO "EVENT" VALUES(1,912,1265478300,900,9,'Podium','English','gnome_closing','GNOME closing talk','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1061,1265457600,900,10,'Podium','English','xmpp_devroom','Welcome to the XMPP devroom','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1062,1265458500,2700,10,'Podium','English','xmpp_magic','The Extraordinary, Magical Powers and Possibilities of XMPP','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1063,1265461200,1800,10,'Podium','English','xmpp_q_a','Stump the XMPP Experts! Open Q&A','','Open question and answers session with the XMPP Council and XMPP book authors.','',0,0);
INSERT INTO "EVENT" VALUES(1,1064,1265463000,1800,10,'Podium','English','xmpp_socnet','Building Federated Social Networks on XMPP','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1065,1265464800,1800,10,'Podium','English','xmpp_social_web','XMPP and the Social Web','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1066,1265466600,1800,10,'Podium','English','xmpp_pubsub','PubSub Gone Wild: Info Sharing at Mediamatic','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1067,1265468400,1800,10,'Podium','English','xmpp_mirabeau','Mirabeau: Creating Personal Media Networks','','Mirabeau: Creating Personal Media Networks and Bridging UPnP Devices over the Internet with XMPP','',0,0);
INSERT INTO "EVENT" VALUES(1,1068,1265470200,1800,10,'Podium','English','xmpp_strophe','You Got Your XMPP in My Website: Using Strophe.js for Fun and Profit','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1069,1265472000,1800,10,'Podium','English','xmpp_lt','XMPP Lightning Talks','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1070,1265473800,1800,10,'Podium','English','xmpp_jingle','Jingle Nodes: An Open Alternative to Skype','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1071,1265475600,1800,10,'Podium','English','xmpp_mu_jingle','Multi-User Jingle: Voice and Video Conferencing with XMPP','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1072,1265477400,1800,10,'Podium','English','xmpp_lt_more','More XMPP Lightning Talks','','','',0,0);
INSERT INTO "EVENT" VALUES(1,894,1265457600,2700,11,'Podium','English','kde_sc_demo','KDE SC 4.4 demo','','KDE has just released the shinyest most complete version of its desktop yet. KDE Software Collection 4.4 uses the leading KDE Platform provided by KDE 4 to provide applications that cover the needs from netbooks to large desktop rollouts.','Jos takes us through the new features in its applications and the progress made by KDE 4 in the last year.',0,0);
INSERT INTO "EVENT" VALUES(1,895,1265460300,2700,11,'Podium','English','kde_pim','PIMp My Desktop','','KDE PIM is a suite of applications to manage your personal data.','Paul takes us through the abilities of Kontact and its related applications. He will look at Akonadi the desktop neutral platform used as the backend for much of KDE PIM.',0,0);
INSERT INTO "EVENT" VALUES(1,1079,1265463000,900,11,'Podium','English','kde_group_photo','KDE Group Photo','','','',0,0);
INSERT INTO "EVENT" VALUES(1,896,1265463900,2700,11,'Podium','English','kde_kdevelop','KDevelop 4','','KDevelop is the IDE from KDE. It can be used for many programming languages and environements. KDevelop 4 rewrites much of the application and is about to be released.','Aleix will take a look at the features and give us tips on getting the most out of your coding time.',0,0);
INSERT INTO "EVENT" VALUES(1,897,1265466600,2700,11,'Podium','English','kde_qtdesigner','Introduction to Qt Designer','','Creating GUI interfaces is easy with Qt Designer.','Sune will take us through making basic and complex user interfaces with this pleasingly easy to use app from Nokia''s Qt division.',0,0);
INSERT INTO "EVENT" VALUES(1,898,1265471100,2700,11,'Podium','English','kde_obs','Spreading KDE with the openSUSE Build Service','','The openSUSE build service is used to build and host packages for SUSE and other distributions.','Will will look at what is hosted on the service and how you can add to it.',0,0);
INSERT INTO "EVENT" VALUES(1,899,1265473800,2700,11,'Podium','English','kde_amarok','Amarok 2.2 Rocking','','Amarok rediscovers your music. It sorts and searchs through your collections, music devices and internet music services.','Sven will take us through the latest features in this rocking application.',0,0);
INSERT INTO "EVENT" VALUES(1,900,1265476500,2700,11,'Podium','English','kde_es','KDE España','','KDE España is the society for KDE developers in Spain.','Aleix will tell us what it does and why it exists.',0,0);
INSERT INTO "EVENT" VALUES(1,1048,1265461200,3600,12,'Podium','English','jboss_camunda','Camunda','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1054,1265464800,3600,12,'Podium','English','jboss_jopr','Systems management with RHQ and Jopr','','Jopr is the open source systems management and monitoring platform from JBoss / Red Hat.  While it is specially tailored towards JBoss projects, it can be easily extended in various ways.','This talk will present the Jopr / RHQ system and its architecture and then talk about the extension points and how to write extensions for monitoring, management and alerting.

This presentation will also talk about the relation to RHQ-project.org, which used to be the upstream to Jopr and which now includes the Jopr bits.',0,0);
INSERT INTO "EVENT" VALUES(1,1049,1265468400,3600,12,'Podium','English','jboss_drools','Drools','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1050,1265472000,3600,12,'Podium','English','jboss_mobicents','Mobicents','','JAIN SLEE is a specification (JSR 240) of a real-time and event-based platform in JAVA. It can be seen as the equivalent of the JEE but for real-time and oriented to Telecommunication, especially NgIN and IMS.','However, it could be used for any other JAVA applications requiring performance. In this talk we will introduce the JAIN SLEE throug the Mobicents project, the first certified-JAINSLEE 1.1 and open source application server from RedHat.

The presentation will cover:
* The JAIN SLEE component model and the event-driven programming
* The mobicents JAIN SLEE 1.2 features and the introduction to EclipSLEE the Service Creation Environment on Eclipse
* IMS example: we will show how we can implement a SIP registrar with JAIN SLEE. We will also show how a JAIN SLEE AS might be integrated in an IMS infrastructure.',0,0);
INSERT INTO "EVENT" VALUES(1,1051,1265475600,3600,12,'Podium','English','jboss_esb','JBoss ESB','','','',0,0);
INSERT INTO "EVENT" VALUES(1,947,1265457600,2700,13,'Podium','English','ooo_extdev','Tips and Tricks for Extension Developer','','The session will give an overview about the Extension infrastructure and will give tips and hints what''s most important to integrate well in OpenOffice.org and to provide a more professional extension. Extensions provide often the necessary connector from OpenOffice.org to other software systems and the better they are integrated the better is the overall user experience and the interoperability.','OpenOffice.org Extensions provide a very good mechanism to extend OpenOffice.org with new and often specialized new functions. The extension infra structure gets better and better and an extension developer should make use of all the available feature to integrate best in the office. The session will give an overview about the Extension infrastructure and will give tips and hints what''s most important to integrate well in OpenOffice.org and to provide a more professional extension. Often extensions are the beginning of more advanced development tasks that will go deeper in the core code of OpenOffice.org whereas extensions use API''s only. The advantage of extensions is that you can work on a standalone mini project that uses official API''s only and that you can learn the basics and secrets of OpenOffice.org step by step. But extensions can not solve all problems and often additional changes in the core or even new API''s are necessary to solve a specific task. But as mentioned before extensions provide a smooth way to get started and to dive deeper and deeper into the large project code base over time. OpenOffice.org is a very huge project and the start to develop with and for OpenOffice.org is not easy and the hype factor is also not the highest one. But it must be something behind this project that big companies hire special people to work on campaigns against OpenOffice.org and open source in general. Is it still David versus Goliath or has the situation changed a little bit? Who knows but you can be part of the huge and worldwide community and can start to develop with and for OpenOffice.org.',0,0);
INSERT INTO "EVENT" VALUES(1,948,1265460300,2700,13,'Podium','English','ooo_docking','New docking windows for a better UI & extension integration','','The main goal of the framework project is to provide low-level functions (like loading/storing documents, generic UI, OLE, filter management) to the application modules. As the generic OpenOffice.org UI is mainly based on framework code many aspects of the Project Renaissance must be implement there. This presentation wants to provide an overview about our latest plans to provide new and powerful docking window functions.','The presentation is split up into four different parts:
# The current state of docking window design
# The new docking window design
# How can extensions profit from the new design
# Future outlook',0,0);
INSERT INTO "EVENT" VALUES(1,949,1265463000,2700,13,'Podium','English','ooo_build','Improving the OpenOffice.org Build System','','The Build Environment Effort is an ongoing effort to update various aspects of the OpenOffice.org build environment.','Some of the aims of this effort require to rethink the basic architecture of how OpenOffice.org is build. This talk with present the results so far and how we are planning to go on.',0,0);
INSERT INTO "EVENT" VALUES(1,950,1265465700,2700,13,'Podium','English','ooo_testing','Just Testing','','OpenOffice.org is too fat and too weird to let you simply apply your standard unit-testing-approach to writing correct code. Over the years, this has lead to the creation of a number of mechanisms within the OOo code base with which OOo developers can test the code they write and compile.','Some of the mechanisms are, erm, creative, some are trivial. But what all the mechanisms have in common is that they all are brittle and all start to fail, in one way or another, sooner or later. Time to clean up. This talk will discuss where we intend to go, and probably tell a couple of anecdotes about where we came from.',0,0);
INSERT INTO "EVENT" VALUES(1,951,1265468400,2700,13,'Podium','English','ooo_workshop','Show me YOUR code','','Show me the code YOU have written and want to be integrated. Talk about, identify and hopefully clear obstacles. Let''s solve remaining problems together.','The last two FOSDEMs I gave an overview of the Calc spreadsheet interpreter core, and showed how to debug and profile the beast. This year it is time YOU show me YOUR code. Go into details. Discuss your solution. Ask questions. If you would like to dive into your code at the workshop I''d appreciate if you made it available in advance so I can take a look. Send a mail to [mailto:erack@sun.com?subject=FOSDEM%20code me]',0,0);
INSERT INTO "EVENT" VALUES(1,952,1265471100,2700,13,'Podium','English','ooo_hidden_pearls','Hidden Pearls - What''s There to ReUse for Other Projects','','This session presents a few examples of uniquely useful code inside OOo, plus a way for other projects to mine those pearls.','This rant http://blog.thebehrens.net/2008/09/29/ooo-non-vision/ (except for the ranting) pretty much conveys the ideas I want to present here',0,0);
INSERT INTO "EVENT" VALUES(1,953,1265473800,1800,13,'Podium','English','odf_tools','ODF Tools and Resources','','This session lists the various ODF tools and libraries that are "out there", and where one can find additional info about ODF itself.','ODF has become a popular document format, but for new developers it isn''t always clear what open source tools exist and where to find them. This presentations aims to list the most interesting tools, libraries, projects and other resources available.',0,0);
INSERT INTO "EVENT" VALUES(1,954,1265475600,1800,13,'Podium','English','odf_server','ODF on the server - ODFDOM architecture','','ODFDOM is the name of the free OpenDocument framework, which was recently published in version 0.75 to support ODF 1.2.','Its overall purpose is to provide the ODF developer community a lightweight programming API in order to easily access and manipulate ODF documents. With its version 0.75, ODFDOM supports all ODF 1.2 elements and attributes, generated from the OpenDocument RelaxNG schema directly into the Java source code. The upcoming presentation will give an overview over the architecture, design ideas and in addition deliver insights about the roadmap and upcoming features.',0,0);
INSERT INTO "EVENT" VALUES(1,955,1265477400,1800,13,'Podium','English','odf_lpod','lpOD – languages & platforms OpenDocument','','Presentation of the lpOD -- languages & platforms OpenDocument','lpOD, is a Free Software project that offers, for high level use cases, an application programming interface dedicated to document processing with the Python, Perl and Ruby languages. It’s complying with the Open Document Format (ODF).',0,0);
INSERT INTO "EVENT" VALUES(1,999,1265457600,900,14,'Podium','English','pgsql_welcome','Welcome to the PostgreSQL devroom','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1000,1265458500,2700,14,'Podium','English','pgsql_9','Developments in PostgreSQL 9.0','','This talk will briefly examine the development process used by the PostgreSQL project over the last year, and take a look back at the new features that have been committed to the source tree for the upcoming 9.0 release, as well as some of those currently in development.','',0,0);
INSERT INTO "EVENT" VALUES(1,1001,1265462100,2700,14,'Podium','English','pgsql_streaming_rep','Streaming replication under the hood','','In this talk, we''re going to peek under the hood of the new Streaming Replication feature.','I am going to introduce the concepts of WAL receiver and sender, how they communicate over the network, how they interact with the rest of the server etc. I''m also going to cover advanced setups like multiple slaves, cascading slaves, and WAL archiving from a slave.',0,0);
INSERT INTO "EVENT" VALUES(1,1002,1265465700,2700,14,'Podium','English','pgsql_hot_standby','Hot Standby Live','','Live demo of Hot Standby, plus discussion of various features and difficulties. Requests for prioritisation of new feature development, with round table discussion and voting.','',0,0);
INSERT INTO "EVENT" VALUES(1,1003,1265469300,2700,14,'Podium','English','pgsql_beyond_unique','Beyond UNIQUE: Exclusion constraints in PostgreSQL 9.0','','PostgreSQL 9.0 introduces the feature Exclusion Constraints, and this talk will present this feature and how to use it to solve this type of problem with a declarative constraint - while maintaining performance and concurrency in the system.','A core feature of a relational database is being able to define constraints on the data, and have the database enforce those constraints. Today, there exists only one kind of constraint that will look at a combination of more than one row in a table - the UNIQUE constraint, often used as a tables PRIMARY KEY. This constraint makes sure no two rows have the same combination of values in the specified columns. But many datamodels contain completely different constraints, such as requiring non-overlapping ranges. For example, the requirement that a resource such as a conference room is not double booked.',0,0);
INSERT INTO "EVENT" VALUES(1,1004,1265472900,2700,14,'Podium','English','pgsql_basel_zoo','PostgreSQL at the Heart of the Basel Zoo POS','','Elephants and Other Wild Animals: PostgreSQL at the Heart of the Ticketing Point of Sale in the Basel Zoo','For 134 years the Basel Zoo, one of the most renowned and beautiful zoos in Europe, has sold entrance ticket by hand. A simple roll of paper tickets and manual book keeping where all that was there. Being a legal incorporated, law forced them to introduce an electronic point of sale system. First of January 2009, the system went into production and, unlike in other Zoos, worked without any problems right from the start. It is now in production for a year and has proven extremely stable and efficient.

The PostgreSQL database is at the heart of the point of sale application and in this presentation Marc Balmer will show how PostgreSQL helped to create an enterprise grade application database which is accessed by different client applications in a distributed network, including low-bandwidth network links. The overall application architecture will be discussed and how PL/PGSQL helped to keep the business logic in the database itself, leveraging client complexity. Details will be given about the Motif based POS application, written in pure C and extended in Lua, as well as the backoffice which is web based and implemented in C and Lua. The presentation is aimed at programmers that want to include PostgreSQL in their application portfolio as well as decision makers that have to decide upon a strategic database platform for their products.',0,0);
INSERT INTO "EVENT" VALUES(1,1005,1265476500,2700,14,'Podium','English','pgsql_most_wanted','Most Wanted: Future PostgreSQL Features','','Based on user feedback, I will discuss the most requested features for PostgreSQL, their implementation status, difficulties, blockers, and future plans.','Items include replication, materialized views, parallel queries, in-place upgrade. The audience is invited to join the discussion.',0,0);
INSERT INTO "EVENT" VALUES(1,1028,1265457600,3600,15,'Podium','English','coreboot_intro','coreboot introduction','','The BIOS and it''s successor EFI are considered by many to be the final frontier for open source software in commodity PCs. This talk introduces the open source BIOS replacement coreboot (formerly known as LinuxBIOS) and the projects that surround it, including many popular payloads that combine with coreboot to make up an innovative firmware for PCs.','The talk also looks at the 10 year long history of the project, describes the current state of development and considers some possibilities for the future.',0,0);
INSERT INTO "EVENT" VALUES(1,1029,1265461200,3600,15,'Podium','English','coreboot_pc_details','coreboot and PC technical details','','A modern PC is quite different from the 1980s original, and while the BIOS still lingers after 30 years it must now solve many tricky problems.','When the original PC with it''s pre-ISA expansion bus was powered on, it was almost immediately ready to run an application. Today''s PC can have several multicore CPUs interconnected by HyperTransport, Front Side Bus or QuickPath, DDR3 RAM on each CPU, and a large number of buses and peripherals. Many components require increasingly complex initialization to be implemented in software. This talk describes the technical challenges encountered by coreboot developers and their solutions.',0,0);
INSERT INTO "EVENT" VALUES(1,1030,1265464800,3600,15,'Podium','English','coreboot_acpi','ACPI and Suspend/Resume under coreboot','','Ever wanted to know more about ACPI? This talk will introduce the software part of ACPI as well as provide the necessary hardware details to get the bigger picture.','A tour through the Coreboot ACPI implementation will be given, and the nitty-gritty details of the suspend and resume procedure will be explained.',0,0);
INSERT INTO "EVENT" VALUES(1,1031,1265468400,3600,15,'Podium','English','coreboot_porting','coreboot board porting','','You don''t like your BIOS? Want coreboot instead? Here is my story...','This talk introduces some strategies for porting coreboot to new hardware. We go over the information gathering stage, data-mining, datasheet usage and common gotchas. The porting of a new motherboard but with existing chipset support, as well as kick-starting a new chipset port, are explained.',0,0);
INSERT INTO "EVENT" VALUES(1,1032,1265472000,3600,15,'Podium','English','coreboot_flashrom','Flashrom, the universal flash tool','','Flashrom is the open source utility of choice to identify, read, write, verify and erase flash chips.','It is commonly used to flash BIOSes from under Linux, *BSD, OpenSolaris and Mac OS X, but it also has the ability to reflash graphics cards, SATA controllers, network cards and one game console. A wide variety of external programmers is supported as well, from ultra-cheap homemade setups to high end commercial machines.
Hotflashing and crossflashing complete the feature set.

This talk introduces flashrom, and explains its structure and implementation. Common issues and future directions are explained, and even a demonstration will be given.',0,0);
INSERT INTO "EVENT" VALUES(1,1033,1265475600,3600,15,'Podium','English','coreboot_bios_reveng','Flash enable BIOS reverse engineering','','Many board makers provide extra write protection for their BIOS chips. The developers at the flashrom project have to devote part of their time on finding out what protection is present and how this can be disabled.','Some of this information comes from the BIOS itself, and the procedures for some common BIOSes, and the tools involved will be introduced in this talk. Part of the time will be spent on digging through an actual BIOS with a crude tool like ndisasm.',0,0);
INSERT INTO "EVENT" VALUES(1,1056,1265462100,2700,16,'Podium','English','ruby_database_comparison','A rubyist''s naive comparison of some database systems and toolkits','','This talk will be a quick comparison of some of the many relational and non relational database systems that can be used with ruby.','I will focus on features, syntax and performance. This is not a talk by a database expert but simply a modest attempt to show the differences between some of the possibilities offered and clear things up a bit.',0,0);
INSERT INTO "EVENT" VALUES(1,1059,1265464800,2700,16,'Podium','English','ruby_mongomapper','Persisting dynamic data with MongoMapper','','What is [http://www.mongodb.org/ MongoDB] and how can you use it in a Ruby project.','Introduction to [http://www.mongodb.org/ MongoDB], [http://github.com/jnunemaker/mongomapper/ MongoMapper] and advanced usage of the tools given by MongoMapper. Short look at other Document Oriented Databases.',0,0);
INSERT INTO "EVENT" VALUES(1,1073,1265468400,1800,16,'Podium','English','ruby_smalltalkification','The Ruby Smalltalkification','','Smalltalk can be considered as the grand father of many modern programming languages. It is also commonly agreed that it is dead; is it really the case?','Ruby is explicitly inspired by Smalltalk (among others) and can be seen as a ''Smalltalk dialect with files''. This short talk will walk through the fundamental differences and similarities between the two languages.

Do expect source code during this presentation.',0,0);
INSERT INTO "EVENT" VALUES(1,1058,1265470200,2700,16,'Podium','English','ruby_ror_good_practices','25 good practices in Ruby on Rails development','','This is a collection of small tips and tricks related to developing web applications using the Ruby on Rails framework, gathered from my personal experience of more than 2 years of work at [http://www.belighted.com Belighted].','For each tip, we will have a look at the underlying motivation and provide code examples to better understand how to apply it to your own applications.',0,0);
INSERT INTO "EVENT" VALUES(1,1057,1265472900,2700,16,'Podium','English','ruby_crbac','Context Based Access Control gem for Rails','','The CBAC system contains the following features:
* Separate authorization logic from your code
* Supports Role Based Access Control. Authorization based on group membership.
* Supports Context Based Access Control. Group membership is determined on user and context of requested resource.
* Easy to use.
* Authorization on the level of controller methods. Specify authorization per controller method.','',0,0);
INSERT INTO "EVENT" VALUES(1,822,1265461200,5400,7,'Other','English','lpi_1','LPI exam session 1','','LPI exam session #1','',0,0);
INSERT INTO "EVENT" VALUES(1,823,1265468400,5400,7,'Other','English','lpi_2','LPI exam session 2','','LPI exam session #2','',0,0);
INSERT INTO "EVENT" VALUES(1,868,1265458500,1800,17,'Podium','English','java_debian_packaging','Packaging Java Software for Debian','','The talk wants to give a brief overview of the current state and recent trends of Java packaging in Debian.','During the half-hour presentation, topics and issues will be outlined.

Afterwards the Room is free for people to stay and discuss. The aim is, to bring together people from different linux distributions to share experiences together with developers of upstream projects.

A wiki site is used to collect discussion points beforehand: [http://wiki.debian.org/Java/DevJam/2010/FosdemProposedTalks/JavaPackaging]',0,0);
INSERT INTO "EVENT" VALUES(1,869,1265464800,1800,17,'Podium','English','java_groovy','Groovy: the cool side of Java','','The purpose of this talk is to introduce Groovy using a practical approach by showing the differences and the improvements that Groovy bring, compared with an older programming language class.

Since groovy is based on the JVM, it is natural to compare it with Java language.','We will start from a couple of java classes and we will rewrite it using Groovy and we will see how Groovy removes the ceremony and give a shorter and more understandable code.

During the talk will be also explained theory concepts around groovy implementations time to time will be faced.
Despite the topic, this talk is open to java and non-java developers.',0,0);
INSERT INTO "EVENT" VALUES(1,870,1265467500,1800,17,'Podium','English','java_lambda_jsr292','Lambda + JSR292','','This talk outline why and how anonymous functions also called lambdas should be implemented using method handle, one feature introduced by JSR 292 in Java VM.','I will introduce a proposed syntax that is slighly different from the one proposed by Mark Reinhold, and explain how the syntax can be translated to a bytecode understandable by a JDK7 VM. Then I will discuss the possible reification of function types. I will finish by demoing a prototype of java compiler patched with lambdas implemented using method handles.',0,0);
INSERT INTO "EVENT" VALUES(1,871,1265470200,1800,17,'Podium','English','java_wizard4j','Wizard4j','','Introduction and a Getting Started to the wizard4j project.','The wizard4j project defines a flowchart xml language to describe flowcharts in a formal way (so this logic is no longer burried in the rest of the code). Next it provides an engine written in java to ''run'' these flowcharts. The target audience for this project are java software developers. Any java application that has some ''flowchart logic'' inside (configuration wizards, helpdesk guidelines, surveys, template preprocessing, ...) can benefit from wizard4j, especially when this logic is complex or requires frequent updates.',0,0);
INSERT INTO "EVENT" VALUES(1,872,1265472900,1800,17,'Podium','English','java_play','Web Development with the Play! framework','','Java web development is often based on a growing stack of software layers. This increasing complexity is impacting productivity and causing frustration of developers in each step of development, maintenance and deployment. The Play framework aims to bring back the fun with a simpler and cleaner stack, introducing conventions over configuration and encouraging RESTful architectures.','Version 1.0 have been released in October 2009 under the Apache 2 Licence. We will present the framework, explain and demonstrate how it is used to develop web applications, and introduce the vision and roadmap for the next versions.',0,0);
INSERT INTO "EVENT" VALUES(1,829,1265533200,2700,18,'Podium','English','reprap','RepRap - Manufacturing for the Masses','','This talk will start by briefly introducing RepRap - the replicating rapid prototyper.','The talk will then look at how a growth of replicator technology may change economic activity, society, and the nature of wealth.  Material costs for a RepRap are currently about 350 EUR.  That means that RepRap is accessible to small communities in the developing world as well as to individuals in the developed world.  The designs for the RepRap machine are being  is distributed free to everyone using the GPL - so people can copy the machines to their friends without limit.

Finally it will examine replicator technology in the biological context, considering both it and human beings to be collaborating and competing replicators in a Darwinian ecology',0,0);
INSERT INTO "EVENT" VALUES(1,854,1265536800,2700,18,'Podium','English','tor','Tor: Building, Growing, and Extending Online Anonymity','','A review and update on Tor, how open source solutions work well worldwide,  where we''re headed, and where we need help from developers like you.','Tor is a tool to protect your online privacy and anonymity.  We rely on thousands of volunteers to run our network, review our code, and help enhance the experience for all.',0,0);
INSERT INTO "EVENT" VALUES(1,867,1265540400,2700,18,'Podium','English','','MINIX 3: a Modular, Self-Healing POSIX-compatible Operating System','','MINIX started in 1987 and led to several offshoots, the best known being Linux. MINIX 3 is the third major version of MINIX and is now focused on very high-reliability and security.','MINIX started in 1987 and led to several offshoots, the best known being Linux. MINIX 3 is the third major version of MINIX and is now focused on very high-reliability and security. When you buy a TV set, you just plug it in and it works perfectly for the next 10 year. We are trying to make operating systems as good as that. The current version of MINIX 3 can detect device driver crashes and some server crashes and automatically replace the failed component without user intervention and without affecting running processes. The talk will discuss these aspects as well as new work.',0,0);
INSERT INTO "EVENT" VALUES(1,798,1265547600,2700,19,'Podium','English','hadoop','Large scale data analysis made easy - Apache Hadoop','','The goal of Apache Hadoop is to make large scale data analysis easy. Hadoop implements a distributed filesystem based on the dieas behind GFS, the Google File System. With Map/Reduce it provides an easy way to implement parallel algorithms.','Storage has become ever cheaper in recent years. Currently one terabyte of harddisk space costs less than 100 Euros. As a result a growing number of businesses have started collecting and digitizing data: Custumer transaction logs, news articles published over decades, crawls of parts o f the world wide web are only few use cases that produce large amounts of data. But with petabytes of data at your fingertips the question of how to make ad-hoc as well as continuous processing efficient arises.

The goal of Apache Hadoop is to make large scale data analysis easy. Hadoop implements a distributed filesystem based on the dieas behind GFS, the Google File System. With Map/Reduce it provides an easy way to implement parallel algorithms.

After motivating the neeed for a distributed library the talk gives an introduction to Hadoop detailing its strengths and weaknesses. It gives an introduction on how to quickly get your own Map/Reduce jobs up and running. The talk closes with an overview of the Hadoop ecosystem.',0,0);
INSERT INTO "EVENT" VALUES(1,801,1265551200,2700,19,'Podium','English','scalingfacebook','Scaling Facebook with OpenSource tools','','This talk will give you a better idea of what it takes to scale Facebook.','From the day that Mark Zuckerberg started building Facebook in his Harvard dorm room in 2004 to today, the site has been built on common open source software such as Linux, Apache, MySQL, and PHP.  Today Facebook reaches over 350 million people per month, is the largest PHP site in the World, and has released major pieces of our infrastructure as open source.

It''s not possible to scale a site like Facebook simply by sharding your databases, rather we''ve developed and contributed to a series of open source infrastructure technologies.  Some of these projects include Cassandra, Hive, Haystack, memcached, and Scribe, where each focuses on solving a specific problem with Thrift allowing them to communicate across languages.  This talk will give you a better idea of what it takes to scale Facebook, a look into the infrastructure we use to do so, and dive into performance work we''re focused on in order to scale PHP to over 350 billion page views per month.',0,0);
INSERT INTO "EVENT" VALUES(1,820,1265554800,2700,19,'Podium','English','','Inside StatusNet: How Identi.ca Works','','The Open Source microblogging server, StatusNet, drives thousands of sites around the Web.','The Open Source microblogging server, StatusNet, drives thousands of sites around the Web. One of the most popular is the original, Identi.ca, with over 120,000 users. Founder and lead developer of the StatusNet project and CEO of StatusNet, Inc., Evan Prodromou will discuss the deep internals of the StatusNet, tell stories about how the identi.ca site has scaled, and forecast the future of Open Source and distributed microblogging on the Web.',0,0);
INSERT INTO "EVENT" VALUES(1,804,1265559300,2700,1,'Podium','English','linuxkernelpatch','Write and Submit your first Linux kernel Patch','','As A core member of the Linux Kernel team, Greg will show us how to write a kernel patch.','This talk will cover the steps necessary to properly compose, describe, and submit a Linux kernel patch.  It will cover the basic usage of git, and how that works with the Linux kernel development cycle.                                                                                                        
Attendees should have a solid grasp of the C language, and know how to build and install, a Linux kernel from scratch (if not,reading the book, Linux Kernel in a Nutshell, free online, ahead of time would be a very good idea.)',0,0);
INSERT INTO "EVENT" VALUES(1,816,1265533200,2700,20,'Podium','English','dojo','Building High Performance Web Applications with the Dojo Toolkit','','The Dojo Toolkit is a robust toolkit for creating JavaScript-based web applications.','The Dojo Toolkit is a robust toolkit for creating JavaScript-based web applications. In this talk you will learn about:

* The origins of the toolkit
* A high level overview of features and project direction and philosophy
* Practical examples and key architectural approaches that may be applied to building any JavaScript-based application',0,0);
INSERT INTO "EVENT" VALUES(1,817,1265536800,2700,20,'Podium','English','mootools','MooTools as a General Purpose Application Framework','','This talk presents the various MooTools projects and how they help with web application development.','This talk presents the various MooTools projects and how they help with web application development. We will focus in detail on the MooTools Core Library and its inner workings. The talk will cover the functionality found in Core including the class oriented inheritance model and the merits of extending the native types in JavaScript. We will also discuss how the Framework extends beyond Browsers into any JavaScript environment and how this can enhance application development.',0,0);
INSERT INTO "EVENT" VALUES(1,1055,1265540400,2700,20,'Podium','English','','Javascript charting with YUI Flot','','Web developers who want to add charts and graphs to their web sites have three options. 
1. Use server side generated chart images 
2. Use flash 
3. Use canvas + javascript','Web developers who want to add charts and graphs to their web sites have three options. 
1. Use server side generated chart images 
2. Use flash 
3. Use canvas + javascript

Option 1 is often the best unless you need some level of interactivity at which point you''re stuck with choosing between flash that has problems with focus on linux, and has never been a favourite of FOSS developers, or using canvas + javascript with incomplete support for Internet Explorer through excanvas.  YUI-flot follows option 3. 

YUI-flot came about as an attempt to bring the popular flot plugin for jQuery into the hands of YUI developers, and in this talk, I''ll cover a little bit about what you can do with YUI-Flot, and a little more about what I learnt while developing it.',0,0);
INSERT INTO "EVENT" VALUES(1,818,1265547600,2700,21,'Podium','English','postgres','Postgresql: Lists and Recursion and Trees (oh my)','','PostgreSQL 8.4 has radical new capabilities inside the database: Windowing functions and Common Table Expressions.','PostgreSQL 8.4 has radical new capabilities inside the database: Windowing functions and Common Table Expressions. You''ll learn about each with practical examples to make your querying days more fun. Time permitting, we''ll do some that are less practical.',0,0);
INSERT INTO "EVENT" VALUES(1,815,1265551200,2700,21,'Podium','English','mariadb','MariaDB: extra features that make it a better branch of MySQL','','MariaDB is an independent branch of MySQL with additional features and patches. This talk will give a technical overview of MariaDB.','MariaDB is an independent branch of MySQL with additional features and 
patches. This talk will give a technical overview of MariaDB, including:

* A walkthrough of extra features available in MariaDB 5.1:
** Extra storage engines (XtraDB, PBXT, Maria, FederatedX)
** Community patches integrated into MariaDB
** Additional features and optimizations
* Compatibility policy between mainline MySQL and MariaDB
* MariaDB''s approach to accepting external contributions
* Further technical directions of MariaDB project',0,0);
INSERT INTO "EVENT" VALUES(1,813,1265554800,2700,21,'Podium','English','couchdb','CouchDB! REST and Database!','','CouchDB how does a document-oriented DB work or how does it work for you?','This presentation takes a look at CouchDB, a distributed, fault-tolerant and schema-free document-oriented database accessible via a RESTful HTTP/JSON API. CouchDB design and replication features solve  the problem of high-traffic websites, distributed peer-to-peer, and offline application, all in the same time. 

The talk will cover the different CouchDB usages and integration in applications and its deployment. It will also present how to build and distribute standalone CouchDB applications on top of CouchDB using its  REST API. CouchDB applications can run on users desktop an be replicated using a P2P system. Data could also be available offline.',0,0);
INSERT INTO "EVENT" VALUES(1,850,1265533200,900,4,'Lightning-Talk','English','kerrighed','Kerrighed: Flexible distributed checkpoint/restart','','Process checkpoint consists in saving the state of a running process, so that the process can be restarted at any time later. Uses include fault tolerance, job suspend that frees memory resources, process live-migration across physical machines. Checkpoint services may checkpoint only single processes as well as full operating systems with processes, file systems, socket states, etc. This talk will present Kerrighed''s application checkpoint/restart and show its advantages in flexibility over other checkpoint services.','Kerrighed is a Single System Image operating system for clusters. It offers the view of a unique SMP machine on top of a cluster of standard PCs.

Kerrighed is implemented as an extension to the Linux operating system (a set of modules and a patch to the kernel). Current development version is based on Linux 2.6.30.

Main available features are:
* Cluster wide process management with customizable load balancing over the cluster (through process migration and remote forking)
* Cluster wide shared memory
* Application checkpointing
* Node addition/removal',0,0);
INSERT INTO "EVENT" VALUES(1,851,1265534100,900,4,'Lightning-Talk','English','apache_ace','Apache ACE: distributing software components','','This talk introduces the Apache ACE project, shows how to use it to assemble software out of reusable components and deploy those components onto an ever increasing number of managed target platforms. Besides giving a high level overview of the architecture, some examples of how to use and extend the project will be shown, and different options given to setup an automated development, QA/testing, staging and production environment.','Apache ACE is a software distribution framework that allows you to centrally manage and distribute software components, configuration data and other artifacts to target systems. It is built using OSGi and can be deployed in different topologies. The target systems are usually also OSGi based, but don''t have to be.',0,0);
INSERT INTO "EVENT" VALUES(1,852,1265535000,900,4,'Lightning-Talk','English','cloudlets','Cloudlets: universal server images for the cloud','','In this talk we will discuss the issue of server images, and how it affects inter-cloud portability. We will describe our vision for a universal format which can be shared and improved as easily as a Git repository, and how we''re implementing it with cloudlets.','Cloudlets are universal server images for the cloud. They''re lightweight, version-controlled, and you can export them to any bootable format known to man: Xen, KVM, Amazon EC2, or just a plain bootable CD. They can be shared and distributed with the semantics of tools such as Git and Mercurial.

Our goal is to build the foundations for truly cloud-independent infrastructures. Our roadmap includes:

  * Multi-image stacks
  * Auto-scaling
  * Automated integration tests
  * In-place image editing
  * Integration with existing VM generation and configuration management tools',0,0);
INSERT INTO "EVENT" VALUES(1,853,1265536800,900,4,'Lightning-Talk','English','wt_dbo','Wt::Dbo: a C++ ORM (Object Relational Mapping) library','','The talk introduces Wt::Dbo. It will be compared to existing ORM and database solutions for C++ and other programming languages. Based on simple examples, you will learn how you can use Wt::Dbo to manipulate objects that are stored in a database from within C++.','Wt::Dbo is a brand new C++ ORM layer. Similar to Hibernate for Java and ActiveRecords for Ruby, Wt::Dbo offers a convenient way to interact with objects which are serialized in a database.

Although the lack of introspection in C++ seems to be problematic to write a decent ORM in C++, Wt::Dbo demonstrates that appropriate use of the C++ template system offers a perfect alternative.

Currently, Wt:dbo contains the following functionality:
<ul>
<li>Automatic schema creation</li>
<li>Mapping of 1-N and M-N relations</li>
<li>Lazy loading of objects and collections</li>
<li>Uses prepared statements throughout</li>
<li>Basic query support</li>
<li>Automatic dirty checking and database synchronization</li>
<li>Built-in optimistic locking (using a version field)</li>
<li>Transactional integrity, even when a transaction fails: dirty objects remain dirty and may later be saved in a new transaction, or may be reverted to their persisted state (unlike Hibernate where you are forced to discard the whole session)</li>
<li>Transaction write-behind for changes, with support for manual flushing</li>
<li>Forces use of surrogate keys</li>
<li>Does not depend on Wt (can be used independently)</li>
<li>Simple backend system: at the moment only SQLite3. We are looking at how we can perhaps can leverage SOCI if it makes its way into Boost.</li>
</ul>',0,0);
INSERT INTO "EVENT" VALUES(1,866,1265537700,900,4,'Lightning-Talk','English','openerp','OpenERP: Design applicactions with OpenObject in minutes','','I propose to show OpenObject in action, how you can customize or develop new modules for OpenERP. It includes: the object and view editor, the workflow editor and the report designer.','OpenERP is a modern Enterprise Management Software, released under the AGPL license, and featuring CRM, HR, Sales, Accounting, Manufacturing, Stock. It is based on OpenObject, a modular, scalable, and intuitive Rapid Application Development (RAD) framework written in Python.

OpenObject features a complete and modular toolbox for quickly building applications: integrated Object-Relationship Mapping (ORM) support, template-based Model-View-Controller (MVC) interfaces, a report generation system, automated internationalization, and much more.',0,0);
INSERT INTO "EVENT" VALUES(1,855,1265538600,900,4,'Lightning-Talk','English','cacert','CAcert: Client-certificates and SSO - the old-new thing','','(or, now we have the chicken, let''s lay some eggs!)

By one means or another CAcert is now ploughing the ground for Single-Sign-On with browser-installed client certificates.  This talk will point to experiences, traps & traumas, and conclude that actually, it''s well worth while and does actually give benefits.  Once you have a chicken, you can lay some eggs.','The community CA -- with a network of 3000+ assurers, we provide one of the largest webs of trust around the world, dedicated to something or other about security.',0,0);
INSERT INTO "EVENT" VALUES(1,821,1265540400,7200,22,'Meeting','English','keysigning','Keysigning Party','','GPG/PGP and CAcert keysigning party','See [http://fosdem.org/keysigning] for details.',0,0);
INSERT INTO "EVENT" VALUES(1,856,1265547600,900,4,'Lightning-Talk','English','constructive_approach','Open-source software: Blaming the unknown, or a constructive approach to technology','','*** NOTE: THIS IS NOT A TALK ABOUT MYSQL - IT''S ABOUT GENERAL ATTITUDE TOWARDS NEW TECHNOLOGIES - I have presented this talk at two open source events where it was received enthusiastically ***
If you don''t know them, they will hurt you. No matter how expert you are, there are holes in your knowledge, and when things go wrong you usually blame what you know the least. So the culprit could be that database, the regular expression engine, the XML parser, the thread engine. What if the problem is between the chair and the keyboard instead? This talk will give you some general insight on the art of software development, encouraging users to rant less and improve their own practice.','The most popular open source database in the world *** NOTE that this talk is not about MySQL ***',0,0);
INSERT INTO "EVENT" VALUES(1,857,1265548500,900,4,'Lightning-Talk','English','kaizendo_org','Kaizendo.org: Customizing schoolbooks the free software way','','Imagine having a schoolbook where a pupil and her teacher can choose the depth of topic, clarity of text, pedagogical method, amount and difficulty of homework - as needed and necessary.

This talk introduces the Kaizendo.org project where this is the ambition - to create a tool which makes authoring of custom books not only possible but as easy as posting a comment on a forum.','Take your regular old-fashioned linear schoolbook and imagine each chapter having alternative versions specifically tailored for the reader.



You''ll have book that works both for pupils that read slow and pupils that zip through the text faster than their classmates. Add alternatives for the teacher (supporting different pedagogical methods, teaching styles), the school (variations on which chapters should be in-depth or which topics should be prioritized) and the parents (a topic summary to read before helping with homework.)



And you''ll have a book that can only be made using free software development methods.



Kaizendo.org - from Kaizen-do, "the way of incremental improvement" - is a project for making these books possible. We have just started, and we need people who would like to help! :)',0,0);
INSERT INTO "EVENT" VALUES(1,858,1265549400,900,4,'Lightning-Talk','English','the_wiki_for_open_technologies','The Wiki for Open Technologies: How to share your projects and knowledge','','CESLA has launched  "The wiki for open technologies " project. This project is addressed to the open source community and to the Internet world on the whole to allow collaboration between different groups and organizations. 

The talk will cover the following topics:

* Thewiki4opentech policy and goals
* What is different in the technological wiki?
* How to contribute. 
* Benefits for contributors and for the open source community.','The Wiki for Open Technologies is an Internet site where you can find technical information and discuss about projects and ideas. Also you can edit almost all of the pages on this site and place new ones. 
This wiki is a project managed by CESLA, the Free Software & Open Content Association of Aragon, Spain. With this project CESLA intends to create a technological content reference for everybody. 

Thewiki4opentech team is working to provide the open source community with a useful tool. This project is based on Mediawiki and implements some improvements to syndicate content with the same or compatible license. A vertical search engine, included in the wiki, allows searching in the most prestigious open source pages. Thewiki4opentech own content, the syndicated content from other wikis and the search engine  cover most of the open source technical information so the community will be able to find the most relevant  information and the main trends related to a topic

Projects are saved as a whole and topics are sorted in tags and not just as an article, this wiki is a site where  projects are well documented and classified. All improvements around projects follow the objective of empowering open source initiatives and innovation in the open source community',0,0);
INSERT INTO "EVENT" VALUES(1,859,1265551200,900,4,'Lightning-Talk','English','qubit','QuBit: Introducing Quantum Superpositions','','The only talk that can use the phrase ''quantum mechanics'' and not sound pretentious! It covers the principles of programming with variables that can hold multiple values at the same time - i.e. quantum superpositions, and how (and why) it''s impossible to know which of those values will be returned if you query the variable. It also details the library itself, and how to use it. (uses the C++ Qubit library, based on Damien Conway''s Perl module)','QuBit is a library to support Quantum Superpositions in C++. This allows each CQuBit variable to hold a number of different values at the same time. Normal mathematical operations can be performed on a QuBit, but they affect every value in the QuBit, at the same time. Binary Operations on two QuBits cause a result based on every possible outcome.',0,0);
INSERT INTO "EVENT" VALUES(1,860,1265552100,900,4,'Lightning-Talk','English','padre_the_perl_ide','Padre, the Perl IDE: Building an open source team, getting the project to users against the odds','','When I started to build Padre, the Perl IDE in June 2008 almost everyone in the Perl community thought it is a waste of effort in a failed project to create something that no one wants.



After 1.5 year, over 50 releases, more than 10,000 commits by many contributors we can say Padre is on its way to become the de facto editor for Perl 5 and Perl 6.



It would have not been possible without the growing support from the Perl community and without the reuse of over 200 CPAN modules written by other people.



In this talk I''ll talk about Padre and how we managed to build the team. How we got included in all the major Linux distributions and what else have we done to build the product?','Padre is a Perl IDE written in Perl 5. It provides special features for editing both Perl 5 and Perl 6 files. It is available on Linux, FreeBSD, Windows, and Mac OSX.',0,0);
INSERT INTO "EVENT" VALUES(1,861,1265553000,900,4,'Lightning-Talk','English','coccinelle','Coccinelle: Finding bugs in open source systems code','','Bugs are pervasive in code. And when one finds one bug there are often
others of the same type lurking in other parts of the code base. The
difficulty then is how to find them efficiently within thousands or
millions of lines of code.

At the University of Copenhagen, in collaboration with researchers in Paris
and Aalborg, we have been developing the Coccinelle program matching and
transformation engine (http://coccinelle.lip6.fr). Coccinelle provides a
language, SmPL (semantic patch language), for writing complex code patterns
that may perform simple searching or that can be annotated with
transformation information. A novelty of Coccinelle is that these patterns
look very similar to ordinary source code. Nevertheless, SmPL patterns can
be made generic using pattern variables, and are matched according to the
semantics of the source code rather than the line-by-line syntax, and hence
we have given them the name semantic patches.

In this talk, we will introduce Coccinelle and the SmPL language, and then
illustrate its use with examples based on bugs that we have found and fixed
in Linux kernel code. In particular, we will focus on how the source-code
like language makes it easy to customize the bug finding process to very
specific problems and to fine-tune semantic patches to reduce the number of
false positives, which plague automated bug finding tools.  To date, over
400 patches derived from the use of Coccinelle have been accepted into the
Linux kernel source tree.','Coccinelle is a program matching and transformation system targeting C code.
Coccinelle provides a language, SmPL (semantic patch language), for writing
complex code patterns that may perform simple searching or that can be
annotated with transformation information. A novelty of Coccinelle is that
these patterns look very similar to ordinary source code. Nevertheless, SmPL
patterns can be made generic using pattern variables, and are matched according
to the semantics of the source code rather than the line-by-line syntax.

In developing Coccinelle, we have particularly targeted Linux kernel code.
Nevertheless, Coccinelle has been applied in the context of other open source
software projects, such as OpenSSL and Wine.  To date, over 400 patches derived
from the use of Coccinelle have been accepted into the Linux kernel source tree.',0,0);
INSERT INTO "EVENT" VALUES(1,862,1265554800,900,4,'Lightning-Talk','English','umlcanvas','UmlCanvas: bringing UML diagrams to the web','','This talk will introduce UmlCanvas in all its appearances: a Javascript library, a hosting service and soon a collaborative platform enabling "Social Modeling". We will illustrate what is possible with the current release and what we''re up to in the near future. The talk will give the audience enough information for them to understand the UmlCanvas concepts, go to the UmlCanvas website and start creating online embeddable diagrams right away.','UmlCanvas is a Javascript library that turns an HTML5 Canvas element into a dynamic and interactive UML diagram editor and presentation tool ... on every HTML page, on and off the web. 
UmlCanvas also offers a hosting service that puts your diagrams online. Design your diagram once, include it in many HTML-based formats: your own pages, your blog, feed readers and even Google Wave. 
Integrating CASE tools and hosted UmlCanvas, creates a collaborative platform that enable modelers to step out of the closed environment of their desktops and extend their modeling into the social web.',0,0);
INSERT INTO "EVENT" VALUES(1,863,1265555700,900,4,'Lightning-Talk','English','jpoker','jpoker: a pure javascript poker client','','jpoker is a poker room client running in the web browser. Unlike its java or flash plugins, it is fully customizable using standard HTML, CSS and images. In less than 3,000 LOC, it provides a poker table, support for multi table tournaments, lobby, user login, user account registration and edition, tournament details and registration, server status and more.','jpoker is a javascript client for playing online poker.',0,0);
INSERT INTO "EVENT" VALUES(1,1089,1265533200,1800,5,'Podium','English','emb_open_mcare','OPEN-MCARE: Open Heart for Elderly Care','','This project uses an ARM embedded open platform to develop the mobile health care system (Open Mobile Care, OPEN-MCARE).','OPEN-MCARE is an assistant with positioning, health care, entertainment, multi-functional operations. If the smooth progress of this project, in addition to the academic contribution to the outcome of this program hope to be able to reduce the real burden of the families and to improve the quality of life for the elderly, so that mobility of the elderly, have a happy, healthy, free and dignified life.',0,0);
INSERT INTO "EVENT" VALUES(1,1088,1265535000,1800,5,'Podium','English','emb_seriesfinale','SeriesFinale, a TV shows'' tracker for Maemo 5','','SeriesFinale is a TV series browser and tracker application for Maemo 5. Its goal is to help you manage the TV shows you watch regularly and keep track of the episodes you have seen so far.','The shows and episodes listings can be retrieved automatically from the web presenting you with information about the subject of the show/episode, director, actors, guest stars, etc. Episodes are presented in a check list view to allow checking and keeping track of the ones that have been already seen.',0,0);
INSERT INTO "EVENT" VALUES(1,1092,1265536800,1800,5,'Podium','English','emb_android_apt','apt-get for Android - with GUI','','When launched, Google created a central point of distributing applications for the Android platform: the Android Market.This approach, although being an undefined standard for most of the major mobile families - Apple as AppStore for their iphone - has limitations, specially in user freedom and flexibility for the development.

Aptoide tries to create a way of sharing applications for Android in a way that the users are in control of what they distribute, how they distribute and what they want to see shared.','We will present the Aptoide concept and compare this to philosophies - central point vs distributed repositories - commenting on each pros and cons, and trying to merged them together.

In the end of the day, this talk proposes to show Android developers a new way of put their applications available which is an alternative of closed and inflexible Google''s Android market.',0,0);
INSERT INTO "EVENT" VALUES(1,1094,1265538600,1800,5,'Podium','English','emb_ofono','Ofono and how to use the Nokia modem plugin','','oFono is an open source project for mobile telephony (GSM/UMTS). It provides a high-level D-Bus API for applications, and a plug-in API for adapting to different modem hardware.','This talk gives an overview of how to run oFono on the Nokia N900 device running Maemo, as well as with (most) Nokia phones over USB.',0,0);
INSERT INTO "EVENT" VALUES(1,1081,1265544000,3600,5,'Workshop','English','emb_cross_build','Cross Build Systems: Present & Future','','There are lots of cross build systems out there these days. While all of these projects have their own focus, concept and design, there are a lot of problems most of us know very well, for example cross build problems,developing patches in an upstream-acceptable way etc.','In this workshop, all participating build system groups will get the opportunity to present three slides and five minutes, in order to outline:
* short project description
* plans for the future
* ideas to collaborate

After that, we''ll collect and discuss those ideas in order to create benefit for both, the involved projects and the whole open-source eco-system.

Any project interested in participation, please write us a mail to crossdev@send-patches.org, in order to organize the presentations.',0,0);
INSERT INTO "EVENT" VALUES(1,1085,1265547600,3600,5,'Podium','English','emb_rockbox','Rockbox: open source firmware replacement for music players','','An overview of [http://www.rockbox.org/ Rockbox], an open source firmware replacement for mp3 players and how we work to reverser engineer portable music consumer electronics devices to put Free Software on them.','',0,0);
INSERT INTO "EVENT" VALUES(1,1091,1265551200,3600,5,'Podium','English','emb_media_controller','Media Controller, harnessing the full power of tomorrow''s video devices','','Back when the first version of the Video 4 Linux (V4L) API was written, video acquisition and output devices available to Linux users ands developers only offered basic functions. With the introduction of hardware compression, V4L showed its limits and the new V4L2 API saw the light of the day in the 2.5.x kernels. Video hardware available today once again pushes the Linux video API to its limits, and there''s no doubt that tomorrow''s devices will offer even more complex features.','Several V4L developers go together during the Linux Plumbers Conference 2009 to discuss a possible future extension to the V4L subsystem called the Media Controller.

Targeted at both embedded and desktop hardware, the Media Controller will let userspace applications access media hardware internals to discover and control device internals. This talk will introduce the Media Controller concept and present the current state of the draft implementation.',0,0);
INSERT INTO "EVENT" VALUES(1,1087,1265554800,3600,5,'Podium','English','emb_dspbridge','ARM and DSP talking to each other in OMAP3: the dspbridge','','The microprocessor OMAP 3430 contains a dual-core architecture consisting on an ARM Cortex-A8 (General-Purpose Processor) and a DSP C64x (as an Image-Video-Audio Accelerator).

The dspbridge is a kernel driver for the OMAP3 architecture. It provides a interface to control and communicate with the DSP, enabling parallel processing in embedded devices.','This talk will be about how to build a system with the dspbridge driver and how to use it for multimedia applications.',0,0);
INSERT INTO "EVENT" VALUES(1,1096,1265558400,1800,5,'Podium','English','emb_nanonote','Copyleft Hardware and the Ben Nanonote','','Making Legal Open Source Hardware in China investigates the Shanzhai technology culture in China, analyzes its positive and negative aspects, and announces a new legal approach to build off the best parts of Shanzhai technology.','This approach uses a mixture of Creative Commons licensing for hardware plans, Free Software licensing for software used to run the hardware, and open patents for the novel technological innovations.

Do you have Qi Inside your hardware? Ben Nanonote is the first real product on market using the approach mentioned above, we will describe it in deep and doing a live demo on the device.',0,0);
INSERT INTO "EVENT" VALUES(1,1090,1265560200,1800,5,'Podium','English','emb_ambienttalk','Scripting Mobile Devices with AmbientTalk','','This talk is about programming mobile handheld devices with a scripting language called AmbientTalk.','This language has been designed with the goal of easily prototyping applications that run on mobile devices interacting via a wireless network. 

Programming such applications traditionally involves interacting with low-level APIs in order to perform basic tasks like service discovery and communicating with remote services. We introduce the AmbientTalk scripting language, its implementation on top of the Java Micro edition platform (J2ME).

AmbientTalk is an experimental object-oriented distributed programming language developed at the Software Languages Lab at
the Vrije Universiteit Brussel, Belgium. The language is primarily targeted at writing programs deployed in mobile ad hoc networks.

AmbientTalk is meant to serve as an experimentation platform to experiment with new language features or programming abstractions to facilitate the construction of software that has to run in highly volatile networks exhibiting intermittent connectivity and little infrastructure.',0,0);
INSERT INTO "EVENT" VALUES(1,941,1265531400,1800,6,'Podium','English','moz_oss_meetups','Open Source Meetups','','Most people use open source software day by day. A fact that most of them do not know: Often, this free software is being developed, documented, marketed and improved by volunteers in their free time. Many open source projects work on fostering the idea of free software and open content, and a lot of users benefit from their efforts. Other than with proprietary software, users can get in direct touch with the communities via blogs, IRC channels, mailing lists or forums.','Despite the modern way of communicating, personal contact still is the best way to get to know each other. Meeting the people behind the names in reality is a great experience, and helps users of finding their way into open source communites to engage themselves. Therefore, Mozilla and OpenOffice.org jointly organize the so-called "Open-Source-Treffen" ("Open Source Meetings") to help open source projects in meeting their end-users and vice versa. Members of the community can get in touch with their users to gather valuable feedback, and open source adopters meet other supporters from their area.
In the German city of Munich, the "Open-Source-Treffen" have been taking place regularly, and the idea is to spread the word for other areas, engaging community members to set up more meetings. Carsten Book of Mozilla and Florian Effenberger of OpenOffice.org, founders of the "Open-Source-Treffen", introduce their vision and tell about the previous experiences. Audience for this talk are open source communities wishing to set up their own meetings as well as interested users who love to learn more about the idea.',0,0);
INSERT INTO "EVENT" VALUES(1,942,1265533200,1800,6,'Podium','English','moz_mozmill','Mozmill','','Automated functional testing','',0,0);
INSERT INTO "EVENT" VALUES(1,943,1265535000,2700,6,'Podium','English','moz_l20n','L20n','','L20n is the codename for a localization architecture taking existing approaches one step further.','The name stands for l10n 2. This sesion will be targeted at tool authors and their users, localizers, on how we can keep simple things simple and expose the power of l20n at the same time.',0,0);
INSERT INTO "EVENT" VALUES(1,938,1265537700,4500,6,'Podium','English','moz_firefox_mobile','Firefox Mobile','','','',0,0);
INSERT INTO "EVENT" VALUES(1,936,1265544000,900,6,'Podium','English','moz_womoz','Women and Mozilla (WoMoz)','','Summary of related FOSDEM events, roadmap for 2010, and reaching out to women developers present at FOSDEM.','',0,0);
INSERT INTO "EVENT" VALUES(1,945,1265544900,2700,6,'Podium','English','moz_messaging','Messaging/Thunderbird','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1076,1265547600,1800,6,'Podium','English','moz_jetpack','Explore Jetpack','','Jetpack is one of the most dynamic project in Mozilla these days.','The talk will be split into three pieces. First, I''ll present the concept and how the project is being developed. Then, I''ll make sure there''s time for your questions. Finally, I''ll try to make sure you know how to join us :)',0,0);
INSERT INTO "EVENT" VALUES(1,1077,1265549400,2700,6,'Podium','English','moz_drumbeat','Mozilla Drumbeat in Europe','','Actions, ideas and projects for an open Internet','',0,0);
INSERT INTO "EVENT" VALUES(1,946,1265553000,2700,6,'Podium','English','moz_lightningtalks','Mozilla Lightning Talks','','Lightning talks on the subject of Mozilla, by various speakers.','==Digitally signing email, why and how ?==
Introduction on digitally signing emails. How does it work. Why Should People sign their emails. Howto sign emails, live demo on how to get started (Ludovic Hirlimann)

==Online Communication in the Mozilla Project==
In virtual teams (like Mozilla) communication is as important as it is challenging. This talk will be about the importance of informal communication and how some of the groups within Mozilla handle it (Kadir Topal)

==I see GECKO==
5 min talk about the "I See Gecko" project, becoming live during this presentation. It''s all about Open Web ... (Bogomil Shopov)

==The Bugzilla REST API==
How you can [https://wiki.mozilla.org/Bugzilla:REST_API use it] to make your Mozilla life easier (Gerv Markham)',0,0);
INSERT INTO "EVENT" VALUES(1,944,1265555700,2700,6,'Podium','English','moz_panel','Mozilla Panel Discussion','','A discussion on Mozilla''s mission - from Firefox to Drumbeat.','',0,0);
INSERT INTO "EVENT" VALUES(1,978,1265530500,2700,8,'Podium','English','dist_cloud','Linux distribution for the cloud','','','',0,0);
INSERT INTO "EVENT" VALUES(1,979,1265533200,2700,8,'Podium','English','dist_perl_cpan','Packaging perl and CPAN modules','','According to a report generated in 2007 less than 10% of the CPAN packages are redistributed by Debian and Fedora and much less by the other distributions.','This is frustrating to the end user as they need to install many other packages directly from CPAN. Because they already have to install from CPAN they don''t care asking the distributors to include those packages nor do they come and help packaging. Hence there are few packages....

In this session we will try to break the vicious cycle of the chicken and the egg and find an improvement to the situation.',0,0);
INSERT INTO "EVENT" VALUES(1,980,1265535900,2700,8,'Podium','English','dist_config_model','Config::Model and configuration upgrades during package upgrade','','For a casual user, editing configuration files in /etc in an intimidating task. Manually managing configuration upgrade is even worse as it requires good knowledge to merge current configuration data with new data coming from new packages.

Config::Model was designed to make user''s life easier by providing a configuration GUI and handle configuration upgrades transparently.','This presentation will explain how to provide these capabilities and will cover:
* the main notions or Config::Model (config tree and model)
* how to create a model 
* how to interface the model with the configuration files
* how package and configuration upgrade is performed 
* how to specify upgrade feature in the configuration model',0,0);
INSERT INTO "EVENT" VALUES(1,981,1265538600,2700,8,'Podium','English','dist_nixos_conf','NixOS'' configuration system','','In this talk, Nicolas Pierron will shortly present the idea behind Nix and NixOS.','Nicolas will explore the mechanism of the NixOS'' configuration system. Finally, he will conclude with some examples to  illustrate the abstraction on top of the system configuration.',0,0);
INSERT INTO "EVENT" VALUES(1,982,1265541300,2700,8,'Podium','English','dist_topgit','Cross distro packaging with (top)git','','The talk presents and discusses a workflow for Debian packages using GIT. The 
workflow aims to be appliable also to other distributions and should even 
allow easy sharing of packaging work done for different distributions.','Additional tools and concepts to be discussed include:
- topgit, a patch tracking solution on top of git
- git-buildpackage, a helper to automate some packaging steps
- Debian Source Format Version 3 with quilt',0,0);
INSERT INTO "EVENT" VALUES(1,983,1265544000,2700,8,'Podium','English','dist_rpm_collab','RPM packaging collaboration','','Fedora, Mandriva and openSUSE are the three largest distributions that use RPM as their package manager. Unfortunately, because of the non-coordinated decisions taken in the past, the packaging in these distributions has taken a slightly different form.','As the result, the packages are not easily interchangeable among these distributions. We tried to identify the differences, the most obvious problems and to propose solutions how to improve this situation. Some of them can be achieved by changing the packaging guidelines and making them more consistent with the rest, the others need modifications in the RPM source code and implementation of its new features. The talk tries to summarize our ongoing efforts in bringing the packaging closer, describe what already has been done and what still needs to be worked on.',0,0);
INSERT INTO "EVENT" VALUES(1,984,1265550300,2700,8,'Podium','English','dist_kiwi','Distribution Image building with KIWI','','The OpenSuSE KIWI Image System provides a complete operating system image solution for Linux supported hardware platforms as well as for virtualisation systems like Xen, Qemu or VMware.','The KIWI architecture was designed as a two level system. The first stage, based on a valid software package source, creates a so called physical extend according to the provided image description. The second stage creates from a required physical extend an operating system image. The result of the second stage is called a logical extend or short an image. 

There are already a lot of projects using the KIWI image system today including the very popular SUSE Studio online appliance builder.

This talk briefly introduces the KIWI image system and shows how to create images based on distributions other than openSUSE.',0,0);
INSERT INTO "EVENT" VALUES(1,986,1265553000,2700,8,'Podium','English','dist_dracut','Dracut - a generic, modular initramfs generation tool','','Dracut is a generic, modular initramfs generation tool, that replaces mkinitrd and nash. Unlike existing initramfs’s, this is an attempt at having as little as possible hard-coded into the initramfs as possible.','The initramfs has (basically) one purpose in life — getting the rootfs mounted so that we can transition to the real rootfs. This is all driven off of device availability. 

Therefore, instead of scripts hard-coded to do various things, we depend on udev to create device nodes for us and then when we have the rootfs’s device node, we mount and carry on. Dracut is modular and very easy to extend and customize.

In this talk you will learn how Dracut works, how to extend Dracut with your own modules and identify problems in this early boot process.',0,0);
INSERT INTO "EVENT" VALUES(1,985,1265555700,2700,8,'Podium','English','dist_suse_studio','SUSE Studio','','This talk will be an overview of the SUSE Studio API, which makes it easy to use SUSE Studio from tools that we would have never imagined.','I will also give a highlight of the interesting appliances and projects that we''ve seen over the last year.',0,0);
INSERT INTO "EVENT" VALUES(1,969,1265533200,2700,8,'Podium','English','dist_tx','Transactional Roll-backs and Upgrades','','As part of the MANCOOSI project, looking to improve upon the upgrade process of packages, Caixa Mágica and several other European partners are researching and developing solutions for various, related topics of the package upgrade process. One aspect is that of looking at whether Roll-Back is feasible and what mechanisms are best for making this sort of approach work alongside existing package meta-installers.','We will state what we define as Roll-Back and the associated problems of trying to achieve this process. To do this we investigate current state-of-the-art mechanisms available for ''Roll-Back'' and configuration management and then state what our current methodology is for trying to tackle and achieve Roll-Back for our apt-rpm based distribution. We outline some of the decisions and assumptions  that have been taken and indicate what the project members believe the outcome will be. 

We will then invite questions from the audience to try and promote a few talking points.',0,0);
INSERT INTO "EVENT" VALUES(1,964,1265535900,2700,8,'Podium','English','dist_youri','The youri project','','YOURI stands for "Youri Offers an Upload & Repository Infrastucture". It aims to build tools making management of a coherent set of packages easier.','Running a package distribution project involves a lot of tasks:
* allow individual maintainers to upload packages in a central repository
* create packages index for packages managers such as urpmi or yum
* synchronise developement resources such as CVS or bugzilla
* advertise new packages
* sign packages numerically
* check individual packages consistency
* check global repository consistency
* etc...

The quick''n''dirty approach of using a pile of dedicated shell scripts, with hardcoded distributer-specific policies, generally results quickly in a maintainance nightmare for admins and a discrepancy nightmare for users. YOURI aims to leverage those issues by providing a generic package management framework, focused on code reusability and modularity.',0,0);
INSERT INTO "EVENT" VALUES(1,965,1265538600,2700,8,'Podium','English','dist_opensuse_buildservice','Cross-distro packaging experience with the openSUSE Buildservice','','','',0,0);
INSERT INTO "EVENT" VALUES(1,966,1265541300,2700,8,'Podium','English','dist_debian_shlibs','Shared libraries in Debian','','','',0,0);
INSERT INTO "EVENT" VALUES(1,967,1265544000,2700,8,'Podium','English','dist_deps','Cross-distro dependency resolution: reusing solvers among distros','','All distributions use some kind of meta-data describing relationships between packages such as Dependencies, Conflicts,  Virtual Packages, etc. Existing package managers are often specific to a packaging format, or even use implicit assumptions on the meaning of package relations in the context of a distribution.','This talk addresses the issue of how we can overcome this seclusion by resolving inter-package relations in a way that is independent from a specific distribution.

We will present CUDF (Common Upgradeability Description Format) which permits to encode upgrade scenarios coming from different packaging systems, including in particular .deb-based and .rpm-based distributions. The format comes with a clear semantics which makes it possible to share resolution tools among distributions, and to adapt general-purpose solvers to the needs of FLOSS distributions.

We also show how, in the context of the Mancoosi project, we are using the CUDF format to improve the solving abilities of state-of-the-art package managers in distributions such as Debian, Mandriva, and Caixa Magica.',0,0);
INSERT INTO "EVENT" VALUES(1,1116,1265546700,2700,8,'Podium','English','dist_debian_ubuntu','Debian and Ubuntu','','When Ubuntu was made public in 2004, it was clear from the beginning that its development would be based on Debian. Five years later, this has not changed at all, and the interactions between Debian and Ubuntu have been the subject of a lot of (heated) discussions over the years.','This talk will first present how the two distributions interact with each other. Then, we will provide a (tentative) overview of the current state of affairs, and will try to give some ideas for the future.',0,0);
INSERT INTO "EVENT" VALUES(1,968,1265550300,2700,8,'Podium','English','dist_tx_pkg','Transactionally Protected Package Management','','The talk will describe current development efforts @rpm5.org to add ACID properties to RPM package management.','All operations involved in installing a package, not only the package metadata, but also the system calls, content, and scripts run by RPM will be logged within a transaction using a two-phase apply -> commit/abort so that all RPM operations can become stateless and invertible.

The talk will specifically focus on and overview of the log management tools and the rpmdb schema changes necessary to use Berkeley DB ACID and transactional log extensions to add ACID properties to RPM package management.

Connections with the parallel Mancoosi WP3 efforts to model/simulate package script behavior using a Domain Specific Language will also be described, time permitting.',0,0);
INSERT INTO "EVENT" VALUES(1,963,1265553000,2700,8,'Podium','English','dist_project_builder','Continuous Packaging with Project-Builder.org','','With the increasing role of FLOSS in enterprise, some development techniques linked to it also know a momentum. Continuous integration (shared sources repository, automatic build, automatic test) is such an example. The new process called continuous packaging should still be promoted and developed as best practice for industry.

Project-Builder.org is a new GPL v2 tool designed to help projects developers producing easily packages for multiple OS and architectures, on a regular basis, from a single source repository.','90% of users and admins prefer to install packages rather than tar files or content from a [D]VCS. But packages don''t necessarily follow the development stream of projects, to package alpha, beta. Giving the possibility for projects to distribute seamlessly packages for whatever step of their development is clearly a gain for the whole community.

The various aspects covered by the tool are:
* only produce software packages (ease integration in deployment severs, provide inheritance mecanisms, and Virtual Machines (VM) or Environments (VE))
* ease the various steps of solution life cycle (controlled ipact of installation/uninstallation, dependencies management, identical deliveries up to the customer, announce management, web site delivery, metadata management)
* help new projects in the provisioning of packages (templates and skeletons for the various supported OS, generated structure, help in VM/VE build)
* Avoid code or metadata duplication, as well as has no impact on the original project (macro system, separate repository)
* Neutral in term of Unix environment (repository, system, package type  agnostic)

These features help reducing the development cost by providing a process, method and tools to realize continuous packaging during the whole project life cycle.
Today the tool supports:
* Multiple repository (none - aka tar balls, SVN, CVS, Git, Mercurial, SVK...)
* Multiple systems ((RPM Linux - Red Hat, openSUSE, Mandriva, ..., deb Linux - Debian, Ubuntu, ..., ebuild - Gentoo, pkg Solaris/OpenSolaris, ...)
* Multiple build environments (local, VM - QEMU, KVM, ..., VE - mock, rinse, pbuilder, ...)
* Multiple repository manager (yum, urpmi, apt, ...)
and this at various phasis (development, test, integration, delivery)

It aims at becoming a tools for the vcs-pkg.org initiative
It''s today used for projects as diverse as FOSSology, MondoRescue, LinuxCOE, GOsa², itself, ...

The presentation will describe the needs of the various people around a FLOSS project (user, admin, developer, packager), how packaging is a must have in the project, why package early, package often is the right mantra, and how Project-Builder.org can help them all achieve those goals.',0,0);
INSERT INTO "EVENT" VALUES(1,970,1265555700,2700,8,'Podium','English','dist_deb_secrets','Debian Secrets: power tools for power users','','This talk will highlight some Debian-specific tools, explain what they do, and how they are useful for both Debian packagers and users.','We hope to compare these tools against similar tools in other distributions.

It is a reworked version of a talk that has been done at DebConf8, where the target audience were power users.',0,0);
INSERT INTO "EVENT" VALUES(1,913,1265533200,900,23,'Podium','English','xd_welcome','Welcome to the CrossDesktop developer room','','','',0,0);
INSERT INTO "EVENT" VALUES(1,914,1265534100,2700,23,'Podium','English','xd_gupnp_rygel','GUPnP & Rygel: Liberating Digital Living','','GUPnP is an object-oriented C library to ease the task for writing UPnP/DLNA applications. Rygel is a collection of DLNA services built on top of GUPnP in Vala language.','I will start the presentation with an introduction of both projects and how they are designed from ground-up for both desktop and mobile environments. After that I will introduce the existing and planed features. I will then introduce the plugin API of Rygel with the help of a Sample plugin, followed by a demo and Q&A session in the end.',0,0);
INSERT INTO "EVENT" VALUES(1,901,1265536800,2700,23,'Podium','English','xd_coherence','Coherence - the digital livingroom and beyond','','Coherence - The Digital Livingroom and beyond (sharing our media with UPnP/DLNA).','After quite some time, where our digital media was limited to dedicated devices - e.g. mp3 players - or spend an isolated life on the PCs of their owners, more and more consumer device appear on the market allowing to easily share these media files in an household (and beyond).

The protocols behind UPnP A/V and DLNA are nowadays implemented in nearly every connected Consumer Electronics device. Being it some first simple clients years ago, continuing with consoles like the PS3 and the XBox 360, media clients like the !PopcornHour,... and now they can be found in amplifiers, TVs and even mobile phones from various vendors.

Using these UPnP A/V and DLNA on our computers and enabling our favourite applications to enter that world, creates a unique landscape where suddenly bridges appear between formerly isolated digital islands.

Coherence is a framework written in Python, that greatly simlifies the entry into the UPnP world. It provides numerous UPnP devices, that can instantly used to serve media-files, act as a gateway to online resources, or to expose the media-db of some application. Others enable controllable media playback for instance via GStreamer.',0,0);
INSERT INTO "EVENT" VALUES(1,1114,1265539500,2700,23,'Podium','English','xd_desktopcouch','Make your users happy, "cloudify" your app with desktopcouch','','There is growing number on devices running Linux and your applications have to adapt to this new environment, using desktopcouch will allow your application to replicate your uses preferences and data over their devices with little development time.','In this dev-talk you will learn how to use desktopcouch as the data back-end of your software.

The talk will focus on:
* Records: What are they and how to work with them and reuse existing ones.
* CRUD operations using desktopcouch.
* Views: A look into views in CouchDb and how are those managed in desktopcouch.
* Use CouchGrid as a way to create TreeView for you UI.

All of the above will be described through a practical exercise using python and PyGTK.',0,0);
INSERT INTO "EVENT" VALUES(1,915,1265544000,2700,23,'Podium','English','xd_packagekit','PackageKit one year on','','PackageKit one year on: what''s changed, and where are we heading','PackageKit is now an established project with a team of developers, and stable front-ends to KDE and GNOME. In this presentation I''ll explain what progress we''ve made in the last year, and what direction the projects are heading. This talk will focus on how application authors can leverage PackageKit, and what PackageKit is now allowing applications to do. We will talk about unresolved issues such as application installation, config file handling (during the transaction) and dealing with complex package management tasks in an abstract daemon.

There will be time left for questions and discussion. It is expected the audience will be technically skilled, and possess a comprehensive understanding of package management.',0,0);
INSERT INTO "EVENT" VALUES(1,916,1265546700,2700,23,'Podium','English','xd_nepomuk_sparql','The Semantic Desktop, SPARQL and You!','','You''ve probably heard about the Semantic Web and the Semantic Desktop. But what lies behind the buzzwords? Let''s look together at at effective examples, running code and actual applications. Be inspired, tame the sparql beast and join the future of desktop computing!','We will demonstrate:
* "Daily Catchup", which uses Tracker to mash together feeds from Facebook, Twitter and Flickr
* Solang, a photo browser built on SPARQL
* FSter, a FUSE file system to browse files by their metadata information
* Gnome Activity Journal: see what you did when.',0,0);
INSERT INTO "EVENT" VALUES(1,902,1265549400,2700,23,'Podium','English','xd_nepomuk','Nepomuk','','Nepomuk makes your desktop semantik. Using RDF is provides context to items in applications making searching and sorting easy and fast.','Sebastian will take us through how it works and what it adds for users.',0,0);
INSERT INTO "EVENT" VALUES(1,918,1265552100,2700,23,'Podium','English','xd_syncml','SyncML','','From the SyncML Protocol to Free and Open Implementations','Data synchronization is still mostly a missing piece in the free desktop puzzle: solutions that are reliable and ready for the mythical Average User just aren''t available. This talk presents the SyncML protocol, introduces the Synthesis SyncML engine (developed since 2000, open sourced 2009) and outlines how SyncEvolution is used as the synchronization solution in Moblin, GNOME and other Linux desktop systems. This is intended to be a technical talk with time for discussion. For a more end-user oriented project presentation, attend the Lightning Talk on Saturday, 18h00.',0,0);
INSERT INTO "EVENT" VALUES(1,1078,1265554800,2700,23,'Podium','English','xd_aegis','Open Accessibility Everywhere: software from AEGIS','','[http://www.aegis-project.eu/ AEGIS] is a European Commission funded project to embed accessibility into mainstream software.','Open source desktops have a head start with regard to accessibility, and we demonstrate some of the projects we are working on:
* A web-cam based gesture switch - smile to click a button :-)
* A "concept coding" plugin for openoffice for symbol based communication
* [http://www.inference.phy.cam.ac.uk/dasher/ Dasher] - that familiar from the GNOME desktop',0,0);
INSERT INTO "EVENT" VALUES(1,987,1265529600,900,24,'Podium','English','mono_opening','Opening','','Welcome to the Mono developer room!','',0,0);
INSERT INTO "EVENT" VALUES(1,988,1265530500,2700,24,'Podium','English','mono_develop','MonoDevelop','','MonoDevelop is an open source IDE primarily designed for C# and other .NET languages.','MonoDevelop enables developers to quickly write desktop and ASP.NET Web applications on Linux, Windows and Mac OSX. MonoDevelop makes it easy for developers to port .NET applications created with Visual Studio to Linux and to maintain a single code base for all platforms.

In this talk, I''ll show the features of the recently released MonoDevelop 2.2, and a sneak peak of what we are planning for the next release. It will be a practical session with examples of how to use and extend MonoDevelop.',0,0);
INSERT INTO "EVENT" VALUES(1,989,1265533200,3600,24,'Podium','English','mono_ruby','The Ruby and .NET love child','','This talk will be about leveraging IronRuby from Mono and moonlight. Depending on the time I''d like to show how you can use IronRuby to easily extend your current GTK, WinForms,.. apps with scripting capabilities.','Perhaps how you can use IronRuby from Asp.NET MVC. If there is still time left I''d like to show you can script the browser and use Moonlight + IronRuby to use ruby as client scriping language instead or in cooperation with JavaScript.',0,0);
INSERT INTO "EVENT" VALUES(1,990,1265536800,3600,24,'Podium','English','mono_edge','Mono Edge','','This talk will focus on the ongoing development efforts in Mono, and explore what are the new challenges that we are tackling.','',0,0);
INSERT INTO "EVENT" VALUES(1,991,1265543100,1800,24,'Podium','English','mono_monotorrent','The evolution of MonoTorrent','','MonoTorrent is an implementation of the BitTorrent protocol written in C# for the .NET platform.','This talk will have two parts. The first part will revolve around the Piece Picking algorithm and how it evolved from a simplistic and inextensible initital implementation to its current highly extensible form as more complex behaviours were required.

The second part will be about the different strategies used to manage the multi-threaded workload. A typical bittorrent download will open about 100 connections so it is critical that the syncronisation strategy used to access any shared state does not prevent the sockets from sending/receiving data, otherwise performance will suffer.',0,0);
INSERT INTO "EVENT" VALUES(1,992,1265544900,1800,24,'Podium','English','mono_simd','Image processing with Mono.Simd','','This talk will focus on putting Mono.Simd -- the layer for enabling SIMD processing in mono -- to work in the field of image processing. All code, no slides.','',0,0);
INSERT INTO "EVENT" VALUES(1,993,1265546700,1800,24,'Podium','English','mono_parallelfx','ParallelFx, bringing Mono applications in the multicore era','','Multicore computer are now part of our everyday life. Most desktop and laptop machines out there bundle a dual-core processor, quad-core processor or even 8-core processor by default. This multiplication of the number of core on the same chip is destined to become the way for manufacturers to remain competitive. However, developers were a bit left out in this process, having written sequential programs for ages whereas they were now required to parallelize their program to make them efficient which isn''t an easy step to take.','That''s why we now see the apparition of framework designed to help programmers to take advantage of this new architecture of processor by hiding away the parallel difficulty under primitives that they are used to. ParallelFx is one of such framework for the Mono and .NET world. By providing several new parallel constructs and concurrent data structures, it allows Mono applications to enter painlessly in this new multicore era.

This talk will cover several points :
* What options Mono provide to speed up applications today
* A bit of background on the framework
* The components ParallelFx provides
* Some how-to and usage of the framework
* Status of ParallelFx in Mono',0,0);
INSERT INTO "EVENT" VALUES(1,994,1265549400,3600,24,'Podium','English','mono_second_life','Building The Virtual Babel: Mono In Second Life','','Second Life is a large, on-line virtual world where avatars dance, fly, shop, play, meet, work, fall in love... and program.','This giant, collaborative development environment is run on a grid of over 30,000 CPUs that simulate the land of Second Life. Since August 2008 Mono has been available as a scripting engine for running interactive content in Second Life and over 27 million user created scripts are now running on Mono in Second Life. This talk will discuss our experiences using Mono in Second Life and our plans for the future.',0,0);
INSERT INTO "EVENT" VALUES(1,995,1265553000,1800,24,'Podium','English','mono_moonlight','Moonlight and you','','Moonlight is an open source implementation of Microsoft Silverlight for Unix systems, developed by Novell. It not only allows existing Silverlight applications to run on Linux, you can also create your own on Linux and MacOS using the MonoDevelop IDE.','In this hands-on presentation we''ll take a look at what Moonlight provides now, what it can do for developers, what tools are there, and how you can have a lot of fun with it.',0,0);
INSERT INTO "EVENT" VALUES(1,996,1265554800,1800,24,'Podium','English','mono_osctool','OSCTool - learning C# and Mono by doing','','In 2007, the Oxford Supercomputing Centre received enough funding to put some infrastructure in place behind their clusters - but found a lack of adequate tools to manage it. This talk covers the progression from Perl-based prototyping to 25kloc of C#, due for GPL release in Q1 2010.','',0,0);
INSERT INTO "EVENT" VALUES(1,997,1265556600,900,24,'Podium','English','mono_smuxi','Smuxi - IRC in a modern environment','','Smuxi is an advanced IRC client that solves the "always available" problem in a graphical environment, providing a graphical alternative to the popular text-based ssh + irssi + screen combination.','In this talk, I will present the current functionality of Smuxi and discuss plans for the future.',0,0);
INSERT INTO "EVENT" VALUES(1,998,1265557500,900,24,'Podium','English','mono_closing','Closing','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1046,1265529600,900,25,'Podium','English','drupal_welcome','Welcome to the Drupal devroom','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1097,1265530500,2700,25,'Podium','English','drupal_views3','Views 3','','With Views 3 there was a chance to clean up the code a bit and implement cool new features. For example group-by support or OR.','',0,0);
INSERT INTO "EVENT" VALUES(1,1038,1265533200,2700,25,'Podium','English','drupal_ahah','AHAH crash course','','Implementing AHAH (Asynchronous HTML and HTTP) requires some Form API voodoo to get it done right. At first instance it can be hard to get a grasp at the concepts of AHAH. If you''re a novice to AHAH, it''s really easy to implement it wrong and hurt the Form API.','Wim Leers'' AHAH helper module simplifies the implementation and with his Hierarchical Select module AHAH can be taken even further. This presentation wraps up everything AHAH.',0,0);
INSERT INTO "EVENT" VALUES(1,1039,1265535900,2700,25,'Podium','English','drupal_mobile','Designing for mobile devices','','Practical presentation on making a mobile device friendly version of your Drupal site.','The presentation is non-technical, and covers mainly configuration and a little bit of css.',0,0);
INSERT INTO "EVENT" VALUES(1,1043,1265538600,2700,25,'Podium','English','drupal_eid','The eID module','','The eID is the Belgian electronic identity card.','The company Coworks
is currently building a module to register and login on a Drupal
environment with the eID card. There is still hard developing work to
be done and there is no release yet. (http://drupal.org/project/eid).
Dieter will give an overview of the module.',0,0);
INSERT INTO "EVENT" VALUES(1,1041,1265541300,2700,25,'Podium','English','drupal_new7','What''s new in Drupal 7','','What is there to look forward to in Drupal 7, and when can we have it?','Learn about CCK-like fields in core, the new testing framework, PDO
Database backend, OPML imports, improved time zone support, better
file handling, safety from badgers, and the free ponies for everyone.
This will be a tour of the user facing and developer oriented features
and changes that will make Drupal 7 hot.',0,0);
INSERT INTO "EVENT" VALUES(1,1042,1265545800,2700,25,'Podium','English','drupal_front','Front end perfomance','','In this presentation on page loading performance Wim continues where
he left off last year. He recently finished his bachelor thesis about
this subject.','In the presentation he explains what the current state
is, and what the next steps are to make Drupal lead in page loading
performance.',0,0);
INSERT INTO "EVENT" VALUES(1,1040,1265548500,2700,25,'Podium','English','drupal_development','How to setup the perfect development environment','','Presentation on how to setup the perfect development environment for
Drupal on Ubuntu including svn, drush, eclipse, debugging and database
sharing.','',0,0);
INSERT INTO "EVENT" VALUES(1,1044,1265551200,2700,25,'Podium','English','drupal_solr','Apache Solr and state-of-the-art search techniques','','The Apache Solr module integrates Drupal with the Apache Solr search
platform.','Solr search can be used as a replacement for core content
search and boasts both extra features and better performance. Among
the extra features is the ability to have faceted search on facets
ranging from content author to taxonomy to arbitrary CCK fields.',0,0);
INSERT INTO "EVENT" VALUES(1,1045,1265553900,2700,25,'Podium','English','drupal_upgrading','Upgrading','','Where do you start when upgrading a website with an active community
around it? How do you preserve the data for thousands of users and
nodes? How do you move away from obsolete modules? How do you limit
downtime to a few hours?','These are common questions we have to answer
when upgrading websites from Drupal 5 to Drupal 6 and adding new
functionality on top of it!',0,0);
INSERT INTO "EVENT" VALUES(1,1098,1265556600,2700,25,'Podium','English','drupal_semantic','Drupal and the semantic web','','As of Drupal 7 will use RDFa markup in core, in this session I will:
* explain what the implications are of this and why this matters
* give a short introduction to the Semantic web, RDF, RDFa and SPARQL in human language
* give a short overview of the RDF modules that are available in contrib
* talk about some of the potential use cases of all these magical technologies','',0,0);
INSERT INTO "EVENT" VALUES(1,919,1265529600,900,26,'Podium','English','altos_welcome','Welcome to the Alt-OS devroom','','Welcome to the Alt-OS developer room at FOSDEM 2010.','',0,0);
INSERT INTO "EVENT" VALUES(1,920,1265530500,900,26,'Podium','English','altos_rosetta','Presentation of the Rosetta OS Project','','The Rosetta OS project is a collaboration by numerous embedded, BSD, and other operating systems to build an OS-independent driver API.','It aims at helping projects in sharing source code and drivers for better hardware support.',0,0);
INSERT INTO "EVENT" VALUES(1,921,1265531400,1800,26,'Podium','English','altos_rtems','Introduction to RTEMS','','Introduction to RTEMS: A Real-Time OS for Embedded Applications','This session gives an overview over the RTEMS project, its distinct features, goals, typical applications and current capabilities. It sketches general requirements for real-time applications, basic RTEMS features, the structural differences between a Linux based and an RTEMS based application, available APIs, available subsystems and the driver models.

The goal of this session is to emphasis the distinct requirements addressed in RTEMS compared to UNIX-like Operating Systems. This should be a good base for further discussions on collaboration with other projects.',0,0);
INSERT INTO "EVENT" VALUES(1,922,1265533200,1800,26,'Podium','English','altos_haiku','Introduction to Haiku','','Haiku is a new open-source operating system that specifically targets personal computing. Inspired by the BeOS, Haiku is fast, simple to use, easy to learn and yet very powerful.','A short introduction to the operating system will be presented, along with a little demonstration.',0,0);
INSERT INTO "EVENT" VALUES(1,923,1265535000,1800,26,'Podium','English','altos_hurd','Why is Anyone Still Working on the GNU Hurd?','','Hurd having been in development for so long, but still not production-ready; and with Linux as a mature free kernel being firmly established as the de-facto standard kernel for the GNU system -- people often wonder: why haven''t developers abandoned the Hurd long ago?','Without going into technical details, this short talk tries to explain the main idea behind the Hurd architecture, which sets it apart from other systems.',0,0);
INSERT INTO "EVENT" VALUES(1,924,1265536800,2700,26,'Podium','English','altos_crossbow','Network virtualisation using Crossbow technology','','Leveraging current hardware capacities becomes one of the major topics in current IT business. Designing tools for deploying network virtualization and effectively controlling virtual network environments from the perspective of network capacities raised demand for a project called Crossbow.','With this technology we could effectively control how an application access to the network and decide how much bandwidth it could use. Also, we could dynamically allocate bandwidth resources giving to the application surplus if needed on behalf of other(s) application(s) whose network resources are underutilized. This is done by creating Virtual Network Interface Cards (VNICs)and dedicating each of them to the different application we want to deploy. In this presentation we''ll show how Crossbow technology work in practice deployed on OpenSolaris.',0,0);
INSERT INTO "EVENT" VALUES(1,925,1265539500,900,26,'Podium','English','altos_gallium','Update on Gallium3D ports to AROS and Haiku','','Gallium3D is a new architecture for building 3D graphics drivers. Initially supporting Mesa and Linux graphics drivers, Gallium3D is designed to allow portability to all major operating systems and graphics interfaces.','We will be showing a quick demo of the recent progress of the Gallium3D ports to AROS and Haiku.',0,0);
INSERT INTO "EVENT" VALUES(1,1099,1265543100,900,26,'Podium','English','altos_flashrom','Porting challenge: Flashrom, the universal flash tool','','Flashrom is the open source utility of choice to read and write flash chips and a real porting challenge because it needs full hardware access from userspace.','Some say that only X.org needs a similar level of hardware access. Flashrom is working under Linux, *BSD, OpenSolaris, Mac
OS X and Windows (somewhat) and people use it to reflash BIOSes, graphics/network/SATA cards, a game console and to control a boatload of external flash programmers.

This talk gives a short overview of flashrom and its architecture, and then goes into detail about the work needed to port it to your favourite OS.',0,0);
INSERT INTO "EVENT" VALUES(1,926,1265544000,1800,26,'Podium','English','altos_kgi_hurd','Porting KGI graphics drivers from Linux to GNU Hurd','','GGI/KGI is a graphics driver framework, offering a clear seperation between actual hardware access and abstraction. The hardware access part was originally a kernel driver for monolithic UNIX kernels like Linux and FreeBSD. This talk is about porting that framework, to work with the hardware access part running as a userspace server process on top of the multiserver microkernel system GNU Hurd.','After a short introduction to GGI/KGI and Hurd architecture, this talk will dwell a bit on the interesting aspects of porting the kernel driver to run as a userspace process instead.',0,0);
INSERT INTO "EVENT" VALUES(1,927,1265545800,1800,26,'Podium','English','altos_dde','DDE - Generic Porting of Device Drivers','','This talk will give a short presentation of the Device Driver Environment (DDE), a library that helps porting Linux and FreeBSD device drivers to other operating systems.','The DDE is divided into two parts, the DDEkit, a generic operating system abstraction layer, and guest-specific DDE''s (currently available for Linux 2.6 and FreeBSD) allowing to run unmodified Linux and FreeBSD device drivers. Currently there exist implementations for TUD:OS, an L4 microkernel based operating system developed at TU Dresden and the Genode operating system framework developed by Genode Labs (Dresden). There are also plans to port the DDE to Minix 3.',0,0);
INSERT INTO "EVENT" VALUES(1,928,1265547600,1800,26,'Podium','English','altos_oss4_haiku','OpenSound System v4 port to Haiku','','OpenSound System (OSS) is the first attempt in unifying the digital audio architecture for UNIX. OSS is a set of device drivers that provide a uniform API across all the major UNIX architectures, released under BSD/GPL licences.','The talk will describe the required steps for the port of OpenSound System v4 to the Haiku operating system.',0,0);
INSERT INTO "EVENT" VALUES(1,929,1265549400,1800,26,'Podium','English','altos_rathaxes','Generating Driver Source Code with Rathaxes','','tba','',0,0);
INSERT INTO "EVENT" VALUES(1,930,1265551200,3600,26,'Podium','English','altos_haiku_handson','Hands-on development with Haiku','','','',0,0);
INSERT INTO "EVENT" VALUES(1,931,1265554800,1800,26,'Podium','English','altos_haiku_no_future','Haiku has No Future','','Haiku has No Future (like most other small OSS Operating Systems)','Many Open Source projects start as small but ambitious endeavors, with the hopes of becoming successful. Though it is fair to say that most do not. By taking some recent examples of successful OSS projects and putting it in a juxtaposition with contemporary queer theory (after all, being alternative is all about being queer), I attempt to construct a new definition of success that hopefully serves as an inspiration for OSS projects.',0,0);
INSERT INTO "EVENT" VALUES(1,932,1265556600,900,26,'Podium','English','altos_xattr','Extended File Attributes, how can we keep them around?','','Many operating systems, wether OpenSource or not, make use, or at least support some form of file meta-data.','',0,0);
INSERT INTO "EVENT" VALUES(1,933,1265557500,900,26,'Podium','English','altos_wrapup','Alt-OS devroom Wrap up','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1017,1265529600,4500,27,'Podium','English','gnustep_meet','GNUstep Developer''s Meeting','','Meet the GNUstep developers face to face, discuss current afairs of GNUstep, share news about the latest development and plans on GNUstep, improve collaboration between the several GNUstep related projects.','',0,0);
INSERT INTO "EVENT" VALUES(1,1021,1265535000,2700,27,'Podium','English','gnustep_towards_gui_10','Towards GNUstep GUI 1.0: what we need to get there and how to achieve this within the next year','','The GNUstep project has existed for 15 years now, still there was no 1.0 release of the graphical framework. This may change within the current year.','This discussion will focus on the outstanding tasks for a 1.0 release of GNUstep gui and how they can be achieved.',0,0);
INSERT INTO "EVENT" VALUES(1,1018,1265538600,1800,27,'Podium','English','gnustep_simple_webkit','Simple WebKit: a simplified WebKit compatible implementation in pure Objective-C 1.0','','Simple Webkit is a reimplementation of major parts of the WebKit Obj-C API (WebView, WebFrame etc.).','Internally it uses pure Obj-C. This keeps requirements towards the compiler low (there isn''t Obj-C++ support for all embedded architectures). Another simplification is that it is completely based on the rendering engine of NSAttributedString and NSTextView instead of having its own. This keeps the code and binaries small for a full (X)HTML 4 compatible WebView (approx. 1 MByte). The presentation describes the internal architecture and the status of CSS and JavaScript integration.',0,0);
INSERT INTO "EVENT" VALUES(1,1022,1265541300,1800,27,'Podium','English','gnustep_etoile','Étoilé: Where it is, where it''s going, why it isn''t there yet','','Étoilé is a Desktop Environment for Unix based on the GNUstep frameworks. It focuses on the notions of modularity and small components, collaboration, persistence and flexibility.','In this presentation, we will take a look at the Étoilé history back to 2004 when the project started, and why we haven''t yet released a version aimed at end users.

Over the years we realized more experimentation time was needed to succeed. Which has gradually led the project to take a more radical and slow path. We will explain how and why we changed our priorities and expanded the scope of the project in several directions.

We will also discuss the project status, our current work and what can be expected in 2010.',0,0);
INSERT INTO "EVENT" VALUES(1,1023,1265544000,2700,27,'Podium','English','gnustep_eoileui','Fast and Flexible UI Development with EtoileUI and Smalltalk','','EtoileUI is a high-level UI toolkit for Étoilé where elements visible on screen are abstract nodes to which pluggable aspects can be bound. The same uniform tree structure is used to describe any kind of structured content (composite document, application User Interface etc.) and the role of each node can be entirely changed at runtime by altering the aspects bound to it.

All User Interface concerns such as layouts, tools, action handlers, styles, model objects etc. are pluggable aspects which can be easily reused and recombined.','In this presentation, we will give a general introduction to the EtoileUI framework available on any GNUstep platform and also Mac OS X (EtoileUI is Cocoa compatible).
We will discuss which problems EtoileUI tries to solve, how it integrates with the GNUstep/Cocoa AppKit, and how it moves away from the monolithic widget model used by most other UI toolkits to support treating the User Interface as a permanent prototype. Finally we will show various examples written in Smalltalk and Objective-C to illustrate some key ideas and their benefits:
* Everything can be changed at runtime
* Represents the whole screen as a composite document
* Closer to the mental model we use to describe a User Interface',0,0);
INSERT INTO "EVENT" VALUES(1,1024,1265547600,1800,27,'Podium','English','gnustep_objc20','Objective-C 2.0: libobjc2 and Clang, current status, plans for the future','','Objective-C support in the main branch of GCC has faltered somewhat in recent years, with no support for any of the new features in what Apple dubbed ''Objective-C 2.0''.  This lack of support for things like declared properties has, increasingly, made it difficult to port code from OS X to other platforms.','More recently, Apple has focused on clang, a new front end for the LLVM compiler infrastructure, supporting C, Objective-C and C++. This has made supporting new language features much easier.

Objective-C also requires a runtime library to implement the dynamic features.  This talk will discuss the GNUstep runtime (libobjc2), which provides most of the features required for Objective-C 2 and it''s support in clang, as well as the plans for the future evolution of the Objective-C support on non-Apple platforms.',0,0);
INSERT INTO "EVENT" VALUES(1,1025,1265550300,1800,27,'Podium','English','gnustep_languagekit','LanguageKit: Supporting other dynamic languages on the ObjC runtime','','The Objective-C runtime library provides a set of functions and data structures used to implement the dynamic behaviour of Objective-C. This is a Smalltalk-like object model, with dynamic message sending and introspection. LanguageKit is part of the Ètoilé project and provides an interpreter, just-in-time, and static compiler back end, using LLVM, for implementing dynamic languages.','This talk will discuss the implementation of LanguageKit and cover some of its current and potential uses. LanguageKit is used to implement Ètoilé''s Pragmatic Smalltalk, which generates classes that are ABI-compatible with Objective-C, meaning that Objective-C and Smalltalk classes can subclass or extend each other, with no bridging overhead.  In common cases Smalltalk performance is similar to that of Objective-C.',0,0);
INSERT INTO "EVENT" VALUES(1,1026,1265553000,2700,27,'Podium','English','gnustep_codemonkey','CodeMonkey, an integrated development environment (IDE) for Étoilé','','Étoilé allows (and encourage) programs to be written in Smalltalk instead of Objective-C, as our Smalltalk implementation,
Pragmatic Smalltalk, directly integrates with the Objective-C runtime.

That way, programmers can get the best of both world, mixing Smalltalk and Objective-C freely. But Smalltalk, being a dynamic language by nature, authorize a more powerful development environment, and CodeMonkey wants to implement such an IDE for Étoilé.','CodeMonkey is heavily based on LanguageKit, and people interested by the low-level implementation of Pragmatic Smalltalk are strongly encourage to assist David Chisnall''s talk!',0,0);
INSERT INTO "EVENT" VALUES(1,1027,1265556600,1800,27,'Podium','English','gnustep_porting_cocoa','Porting Cocoa apps to other platforms: what works, what doesn''t, what to do to make porting easier','','GNUstep began life as an implementation of the OpenStep specification. Now, the most well-known implementation of OpenStep is called Cocoa and is the recommended way of developing software for Mac OS X and the iPhone. GNUstep has continued to track these changes, and has become a good way of porting code from Mac OS X to Windows or *NIX.','This session will begin with a short talk, covering the overall state of GNUstep from the perspective of a Cocoa programmer, followed by a short demo moving an example application from OS X to FreeBSD.',0,0);
INSERT INTO "EVENT" VALUES(1,1020,1265558400,900,27,'Podium','English','gnustep_ocpp20','ocpp-2.0: a preprocessor approach to translate Objective-C 2.0 extensions to Objective-C 1.0 for (older) platforms','','With the introduction of OS X 10.5 Apple had defined an gcc-extension for Objective-C which brings many interesting features to the language: garbage collection, properties, synchronization, fast enumerations, dot-notation for getters and setters, code blocks, etc.','Although Apple provides their extensions back to gcc, integration is slow because it has to be tested against all other gcc features and also needs special considerations for different target architectures. So let''s dicsuss another approach: write a preprocessor that maps the new Obj-C 2.0 features back to any existing Obj-C 1.0 compiler (plus some library calls if needed). This should allow to faster follow new developments of the language. The talk offers for discussion a flex/bison grammar for Obj-C 2.0 and some strategies for translating the new features.',0,0);
INSERT INTO "EVENT" VALUES(1,1006,1265529600,900,28,'Podium','English','nosql_welcome','Welcome to the NoSQL developer room','','','',0,0);
INSERT INTO "EVENT" VALUES(1,1007,1265530500,2700,28,'Podium','English','nosql_fun_profit','NoSQL for Fun & Profit','','An introduction to the NoSQL scene: the subfamilies, the projects, as well as their advantages & drawbacks compared to each other or traditional SQL systems.','1. 40 years in the desert: yes, the relational model is actually celebrating its [http://portal.acm.org/citation.cfm?id=362685 40th birthday] this year. Let''s take an unbiased look about what’s great and not-so-great about it.

2. A not-so-novel idea: precursors & roots of NoSQL systems from the 70s to the 00s. NoSQL projects are not just defined in opposition to SQL; they come from approaches as old or sometimes older than the relational model itself.

3. The odd couple family: why those very separate projects, efforts and models have been grouped together under one brand in the public’s mind. Plus, a possible categorization of the sub-families within the movement.

4. “What''s in a name? That which we call a NoSQL system, by any other name would be as frackin’ sweet”: Obligatory, rapid mention of the controversy around the name and why nobody should care.

5. SQL vs. NoSQL, Live from... THE THUNDERDOME: a breakdown of where NoSQL sub-families tend to shine (and where SQL should probably be used instead.)

6. It''s Alive: production examples of NoSQL systems.

7. (If time allows.) The road ahead: future developments, business development possibilities, missing approaches & projects.',0,0);
INSERT INTO "EVENT" VALUES(1,1008,1265533200,2700,28,'Podium','English','nosql_mongodb_intro','Introduction to MongoDB','','MongoDB is a fast, scalable database that was designed for web development.','This talk will cover:
* Scaling with MongoDB (replica pairs, master/slave, sharding)
* Getting started - CRUD and the JavaScript shell
* Creating schemas for a document-oriented DB
* Interesting features for developers (capped collections, file storage, upserts and more)

MongoDB''s goals are:
# Be easy to learn and simple to deploy
# Have the scalability BigTable clones but with dynamic queries
# Have the speed of key value stores but with secondary indexes
# Be a floor wax and a dessert topping

Maybe not that last one.

MongoDB is being used by SourceForge, EA Games, Github, the New York Times, and tons of other companies.',0,0);
INSERT INTO "EVENT" VALUES(1,1009,1265536800,2700,28,'Podium','English','nosql_hbase','My life with HBase','','HBase is an Open Source implementation of Google''s BigTable architecture. Its goal is the hosting of very large tables - billions of rows, millions of columns - atop clusters of "commodity" hardware.','This talk reports on findings along the way of setting up HBase clusters of various size and use. It addresses technical challenges that were faced during the setup as well as best practices developed along the way. More in detail the talk will address:
* HBase - What is it? How does it compare?
* Cluster Requirements
* Design decisions
* Status Quo
* Future/Roadmap

Lars George is the CTO of [http://www.worldlingo.com/ WorldLingo] and uses HBase to host their Multilingual Archive. He also advises those who want to know more about HBase in his (self proclaimed) position as the [http://www.larsgeorge.com/2009/05/european-hbase-ambassador.html European HBase Ambassador].',0,0);
INSERT INTO "EVENT" VALUES(1,1010,1265539500,2700,28,'Podium','English','nosql_cassandra','The Cassandra distributed database','','[http://incubator.apache.org/cassandra/ Apache Cassandra] is a highly scalable second-generation distributed database, bringing together [http://www.allthingsdistributed.com/2007/10/amazons_dynamo.html Dynamo]''s fully distributed design and [http://labs.google.com/papers/bigtable.html Bigtable]''s ColumnFamily-based data model.','Cassandra is used at Facebook, Digg, Twitter, Mahalo, Ooyala, SimpleGEO, Rackspace, and other companies that need high scalability, availability, and fault tolerance.

This talk will cover
* Cassandra architecture and data model
* Case studies: what people are using Cassandra for in production
* Road map: where Cassandra development is headed',0,0);
INSERT INTO "EVENT" VALUES(1,1011,1265544900,2700,28,'Podium','English','nosql_couchdb','CouchDB, a database designed for the web and more','','[http://couchdb.apache.org/ Apache CouchDB] is a distributed, fault-tolerant and schema-free document-oriented database accessible via a RESTful HTTP/JSON API. CouchDB design and replication features solve  the problem of high-traffic websites, distributed peer-to-peer, and offline application, all in the same time.','This talk  won''t be redundant with the main track. After a  really quick look on CouchDB it will show you how CouchDB uses the web standards to serve your data on the desktop or on the web and how the [http://benoitc.github.com/couchapp/ Couch Apps] can be used. Some real usages will be used as example.',0,0);
INSERT INTO "EVENT" VALUES(1,1012,1265547600,2700,28,'Podium','English','nosql_mdb_mdbx','MDB and MDBX: Open Source SimpleDB Projects based on GTM','','M/DB is an Open Source emulation of Amazon SimpleDB, whilst M/DBX is an Open Source Native XML Database based around the SimpleDB HTTP-based API model. Both projects have been built on top of the GT.M NoSQL database.','This talk will briefly summarise the capabilities of these two databases and typical use-cases for which they are designed.  It will also examine why GT.M was chosen as the underlying NoSQL database technology on which they were built.',0,0);
INSERT INTO "EVENT" VALUES(1,1013,1265551200,1800,28,'Podium','English','nosql_gtm','GT.M and OpenStreetMap','','OpenStreetMap is a collaborative mapping project inspired by Wikipedia.  The heart of OpenStreetMap is its geo-data.  All geographic elements are described using a simple database structure and free-form tagging.  A road may be described by tagging it as highway=motorway, a hospital by amenity=hospital, a lake by landuse=water, etc.','The main database uses PostgreSQL and is accessed exclusively through a REST based API. It receives continuous updates from a 30,000 strong community of users. Consequently, in order to maintain acceptable performance, queries on the database are restricted to simple rectangular areas of no more than 0.25 square degrees.

The challenge was to mirror this database and provide an API that permitted queries on larger areas and provided extended query capabilities, such as the ability to find hospitals or fire stations or bars.  We chose GT.M because of it''s a high performance schema-free database that would handle key/value pairs economically and scale well to accommodate the continuous growth of the data.',0,0);
INSERT INTO "EVENT" VALUES(1,1014,1265553000,2700,28,'Podium','English','nosql_mapreduce_couchdb','Comparing the MapReduce way in CouchDB with the SQL way in a RDBMS','','Using NoSQL data stores makes you change the way you design and query data, so you have to learn new tools and methods to get the full power of your NoSQL DB. In this session we will focus on how to stop thinking ''SQL and relations'' and start thinking ''views and MapReduce'' with CouchDB.','Our first challenge will be to query our documents with flexibility to get the data we need. To handle this, we will show how we can translate our good old SQL SELECT queries into Map and/or Reduce functions.

The second challenge of our session will be to design a model both able to deal with the absence of relations between data and easy to query against. After describing basic but not totally satisfying solutions to this problem, we will delve into a more CouchDB-compliant way.',0,0);
INSERT INTO "EVENT" VALUES(1,1015,1265555700,1800,28,'Podium','English','nosql_scalable_cms','Designing a scalable content management system on NoSQL technologies','','This talk discusses what it takes to design a scalable and searcheable content management system.','* Which design decisions do we take?
* What NoSQL technologies do we choose and why?
* How do we model a CMS schema on top of them?
* What are the challenges we face to provide CMS and search functionality in a scalable and highly available environment?',0,0);
INSERT INTO "EVENT" VALUES(1,1016,1265557500,900,28,'Podium','English','nosql_closing','NoSQL closing','','Parting remarks, required reading list.','',0,0);
INSERT INTO "EVENT" VALUES(1,878,1265530500,1800,29,'Podium','English','mysql_phpmyadmin','State of phpMyAdmin','','phpMyAdmin is still evolving. New features in version 3.3 include changes tracking, replication support and database synchronization.','Other lesser known features like data transformation and graphical relational manager will be covered as well.',0,0);
INSERT INTO "EVENT" VALUES(1,879,1265532300,1800,29,'Podium','English','mysql_mmm','Multi-Master Replication Manager for MySQL','','* Introduction to MySQL high availability with MMM
* MMM architecture overview
* Pros and cons
* Examples of usage','',0,0);
INSERT INTO "EVENT" VALUES(1,880,1265534100,1800,29,'Podium','English','mysql_beyond_ga','Beyond MySQL GA: patches, storage engines, forks, and pre-releases','','There is more to the MySQL server than MySQL 5.1 GA. There are a lot of patches available that are not included in the official MySQL source tree. There are several new or enhanced storage engines.','There are a handful of branches of the MySQL source code maintained by community members. And there are official MySQL milestone releases and snapshots. But to benefit from all of this, one has to know that they exist, and know how to use them.

In my talk, I will first give an overview of what community enhancements of various kinds are available. I will then go through the options for using these enhancements, including using pre-build binaries from various sources, building from alternative source trees, building storage engine plugins, and patching upstream MySQL sources.',0,0);
INSERT INTO "EVENT" VALUES(1,881,1265535900,1800,29,'Podium','English','mysql_drizzle','Drizzle, A MySQL fork for the Web','','The Drizzle project is building a database optimized for Cloud and Net applications.','It is being designed for massive concurrency on modern multi-cpu/core architecture. The code is originally derived from MySQL. The code has been simplified by removing many of the original features (Stored procedures, triggers, views, some types etc). Other features are being moved from the core to plugins.',0,0);
INSERT INTO "EVENT" VALUES(1,883,1265537700,1800,29,'Podium','English','mysql_galera','Galera Replication for MySQL','','This session will present the current state of Galera replication project.','* High level overview of Galera replication method
* Contents of recent MySQL/Galera 0.7 release (fully open source)
* Feedback and experiences from the field
* New benchmark results
* Short term road map, 0.8 development status',0,0);
INSERT INTO "EVENT" VALUES(1,884,1265539500,1800,29,'Podium','English','mysql_maintenance','Daily maintenance of big databases/tables','','This talk is about maintaining (or trying to maintain) big databases with large tables with a minimum of downtime and the tools helping for those tasks.','* Configure ibdata
* Backup ?
* Clean the data (optimize and archiving)
* Status of long queries in realtime

A short overview of innotop, maatkit, ptxarchiver, ...',0,0);
INSERT INTO "EVENT" VALUES(1,889,1265541300,1800,29,'Podium','English','mysql_sharding','Sharding for the masses','','The Spider storage engine, a plugin for MySQL 5.1 and later, is an extension of partitioning. Using this engine, the user can deal transparently with multiple backends in the server layer.','This means that the data is accessible from any application without code changes. This lecture will briefly introduce MySQL partitioning, and then shows how to create and use the Spider engine, with some practical examples. This talk covers the latest version of the Spider and the Vertical Partition engines, including the related technology of UDFs that come with the engines. Practical instructions of how to install and use these technologies will be provided during the session.',0,0);
INSERT INTO "EVENT" VALUES(1,886,1265544900,1800,29,'Podium','English','mysql_pbxt','Effective SSD for your Database - a PBXT Primer','','In this session it will shown how to efficiently combine SSD and HDD storage for the benefit of performance of a MySQL database. Examples involving the PBXT storage engine will be demonstrated.','',0,0);
INSERT INTO "EVENT" VALUES(1,887,1265546700,1800,29,'Podium','English','mysql_perf','10x performance improvements - A case study','','Taking a client from a 700ms (at times 1-2 seconds) page load time to a consistent 60ms is a great success story for improvement in database performance. In this presentation we will outline the steps taken and what can be applied to any website as one model to use in evaluation of your website.','While part of a longer talk, we will be reviewing the highlights including:
* Identify what is truly slow and high volume queries
* Choosing the right indexes including unique indexes, concatenated and partical indexes
* Choosing the right storage engines (MyISAM, InnoDB and Memory)
* Removing load including synchronous/real-time queries, master load, locking and sharding
* The best performance improvement for a SQL statement is to eliminate it
* Quantifying improvements made 

The 10 Points are:
# Monitor, Monitor, Monitor
# Identify problem SQL
# Analyze problem SQL
# Indexes
# Offloading master load
# Improving SQL
# Storage engines
# Caching
# Sharding
# Handling database maintenance 

Bonus: Front end improvements',0,0);
INSERT INTO "EVENT" VALUES(1,888,1265548500,1800,29,'Podium','English','mysql_maatkit','Correcting replication data drift with Maatkit','','Replication with MySQL is very easy to set up but also very easy to break. As soon as inconsistencies are introduced, the master and the slaves start being desynchronized - and most often, you have no way to be quickly and efficiently aware of the problem as MySQL offers no built-in mechanism to check data consistency between servers.','Fortunately Maatkit has a neat solution with 2 nice scripts: mk-table-checksum, which is a tool to detect inconsistencies between a master and its slaves and mk-table-sync, which can correct automatically these problems detected with mk-table-checksum.

This session will show you first how to use both tools depending on your replication setup (master-slaves or master-master) and then how to get the most from the multiple options that are available.',0,0);
INSERT INTO "EVENT" VALUES(1,885,1265550300,1800,29,'Podium','English','mysql_python','MySQL and Python: an overview','','There has been lots of chatter about other languages, but not much about Python. This talk will give an overview of what is available to connect to MySQL, and also introduce MySQL Connector/Python.','',0,0);
INSERT INTO "EVENT" VALUES(1,891,1265552100,1800,29,'Podium','English','mysql_ha','MySQL HA overview','','Database High Availability is often the core component to build a higly available infrastructure.','This presentation will guide you trough the different options available with their advantages and disadvantages when choosing a method to setup a Highly available MySQL setup.

We''ll cover MySQL Cluster, MySQL DRBD, MultiMaster based HA setups and different others including a look at how to integrate them with the Operating System.',0,0);
INSERT INTO "EVENT" VALUES(1,892,1265553900,1800,29,'Podium','English','mysql_refactoring','Refactoring Stored Routines','','Although MySQL stored routines have their drawbacks, especially performance-wise, they still have their use. However, there are many things that can go wrong, and in many cases, observing a few principles, and adopting a few coding habits can have huge benefits for performance and maintainability of your stored routines.','In this presentation, I will present a few cases and perform a few stepwise improvements to refactor the stored routine. Benchmarks are presented to show how each change improves performance.',0,0);
INSERT INTO "EVENT" VALUES(1,890,1265555700,1800,29,'Podium','English','mysql_gearman','Gearman for MySQL','','Gearman is a client/server infrastructure for generic tasks, usable on distributed servers, with little worry about the details.','No matter what language you speak, Gearman can meet your needs in C, PHP, Perl, Ruby, shell scripting, and several more. Gearman can also work in conjunction with MySQL, either using UDFs, or simply through its basic architecture. This talk will show examples of how to use Gearman for remote installation and how to call functions written in Perl from any other language or from inside MySQL server, with no knowledge of Perl at all.',0,0);
INSERT INTO "EVENT" VALUES(1,1107,1265529600,1800,30,'Podium','English','openmoko_history','Openmoko: 20 Minutes of history','','This presentation gives a short overview about how it came to the Openmoko project its successes and its failures.','',0,0);
INSERT INTO "EVENT" VALUES(1,1108,1265531400,2700,30,'Podium','English','openmoko_android','Android on Freerunner','','Android on Freerunner: Past, present and future of porting Android on the Openmoko Freerunner GTA02','The Android on Freerunner project aims at porting Android to the Openmoko Freerunner GTA02. The current working release is based on the work done by Koolu for Android Cupcake and includes patches by the community.

In this talk, the project background is explained. A few words are dedicated to the Openmoko Freerunner and why it''s considered as a true open phone. We will present the overview of the current functionalities of Android on the Freerunner.

Looking at the roadmap, we cast some light on the short term and longer term objectives.

This will a great opportunity to meet the people behind the project and see Android on the Freerunner in action.',0,0);
INSERT INTO "EVENT" VALUES(1,1109,1265534100,2700,30,'Podium','English','openmoko_freesmartphone','Freesmartphone.org: DBus-Middleware for mobile devices','','This presentation gives a look about the freesmartphone.org mobile device middleware, its services, its target platforms, and how it can be used easily on the command line.','',0,0);
INSERT INTO "EVENT" VALUES(1,1110,1265536800,1800,30,'Podium','English','openmoko_shr','SHR: A FSO based Openembedded distribution','','SHR is currently the most popular distribution for the OpenMoko FreeRunner and intends to be successful on other devices too. SHR uses E17 as UI, is build around the telephone API of freesmartphone.org and is build with the build-framework from openembedded.org.','SHR is a community driven GNU/Linux distribution for smartphones. It currently targets Openmoko models Neo 1973 and Neo FreeRunner, but is not designed for these only.',0,0);
INSERT INTO "EVENT" VALUES(1,1111,1265538600,1800,30,'Podium','English','openmoko_hackable_1','hackable:1, a Debian/Gnome distribution for hackable devices','','hackable:1 intends to implement the Gnome Mobile platform with a Debian base on embedded phones.','The Openmoko is the currently the most open phone and  therefore the first platform hackable:1 runs on.',0,0);
INSERT INTO "EVENT" VALUES(1,1034,1265544000,2700,31,'Podium','English','xorg_shiny','Polishing X11 and making it shiny','','There are a few niggles about X11 today that mean every embedded device vendor patches the server in various unpleasant ways, whereas on the desktop it just looks suboptimal and we suck it up.','This talk will cover a few parts of X11, such as client-side cursors, the video API, Composite, RandR, which currently need to be improved to make X11 look as good as it possibly can, without going to Wayland or X12.',0,0);
INSERT INTO "EVENT" VALUES(1,1035,1265547600,2700,31,'Podium','English','xorg_stack','The free software desktop’s graphics driver stack','','4 years after the modular X tree was released, we can clearly see that we did not fully satisfy all expectations and that we are really holding the free software desktop back.','In this talk, the current situation gets analysed, and the next step, providing more integrated graphics driver stacks, a change that will make life easier for all involved, is introduced and demonstrated.',0,0);
INSERT INTO "EVENT" VALUES(1,1036,1265551200,2700,31,'Podium','English','xorg_gpu_userspace','GPU Userspace - kernel interface & Radeon kernel modesetting status','','The GPU is one of the most complex piece of hardware in modern computer. With kernel modesetting, more part of the driver move from userspace to the kernel allowing a cleaner support for suspend/resume and others GPU specific handling. The complexity of OpenGL driver, and also driver for new API such as OpenCL, are in userspace and will more than likely stay 
there.','This presentation will look at the unique problem of GPU kernel API to userspace. How userspace can interface with the kernel to submit GPU command in an as efficient as possible way. A brief review of what have been done and what is done now for various GPU, and insight on what might be better solution in the future will be given. Last part of the presentation will devolve to the status of radeon kernel modesetting which is now the largest driver inside the linux kernel with more the 70 000 lines of code and supporting more than 7 different GPU families.',0,0);
INSERT INTO "EVENT" VALUES(1,1037,1265554800,2700,31,'Podium','English','xorg_epaper','X on e-Paper','','e-Paper is a relatively new display type with very unusual characteristics. Some of them, such as greyscale, bring back memories of the distant past, whereas others, like a 1Hz refresh rate, are completely unique.','This talk will outline the special requirements that e-Paper imposes on X.',0,0);
INSERT INTO "EVENT" VALUES(1,873,1265536800,1800,17,'Lightning-Talk','English','java_lightning','Last minute lightning','','If you missed the dealine for talk proposal submissions for this devroom, please come to the devroom on Sunday morning and present your project in 5 minutes (or less) in this free and open source Java lightning talk session.','',0,0);
INSERT INTO "EVENT" VALUES(1,874,1265539500,1800,17,'Podium','English','java_gervill','Gervill Software Synthesizer: Effects processing','','This talk will focus on insert effects and how they are to be used in Gervill Synthesizer.','Currently insert effects haven''t been implemented and it has been the main user request. Insert effects are used to tweak and enhance performance on MIDI playback. For example distortion effect applied to guitar instrument to create buzzy sound.

There will also be audio demonstration on these features.',0,0);
INSERT INTO "EVENT" VALUES(1,875,1265542200,1800,17,'Podium','English','java_jwt','Simplify web application development with JWt','','JWt is a relatively new Java library for developing interactive web applications that may be deployed within standard Java Servlet containers. JWt 3.1 is a feature-complete pure Java sibling of Wt 3.1, the well known C++ web toolkit which has been around for years.','This talk will introduce the audience to the basic JWt concepts. You will learn how JWt handles events, how JWt applications are deployed, and why applications written in JWt will be faster and cause less server load than many other frameworks.

Unlike many page-based frameworks, JWt was designed for creating stateful applications that are at the same time highly interactive (leveraging techniques such as AJAX to their fullest) and accessible (supporting plain HTML browsers), using automatic graceful degradation or progressive enhancement.

Come to this talk if you have an interest in doing web application development and prefer a pragmatic approach to developing web user interfaces very much like you have developed desktop user interface (e.g. in Swing).',0,0);
INSERT INTO "EVENT" VALUES(1,1047,1265544900,1800,17,'Podium','English','java_arm','The ARM Optimised Interpreter and Thumb2 JIT','','The ARM architecture in constrained devices such as smartphones and low end netbooks presents unique challenges for the VM writer. The ARM Optimised Interpreter delivers performance improvement of up to five times the C interpreter in the OpenJDK Zero port while maintaining smooth performance throughout. This talk looks at the techniques used and explores how they could be extended to other architectures.

The second part of the talk will look inside the Thumb2 JIT. The principle design goal of the Thumb2 JIT was to optimise time of first execution rather than peak performance. As such the design goals were to produce a JIT giving very fast compile time while generating reasonable and compact code.','The ARM architecture is typically used in constrained devices such as smartphones and low end netbooks. Typically a constrained device has
* Single, not multiple core
* Relatively fast core speed (800MHz)
* Small primary cache (32K I+D)
* Small secondary cache
* Slow memory system (typically 300nS)
* Small memory system (typically 512M)

This means that the system is almost completely constrained by the memory system. A single cache miss can cost up to 270 cycles.

This presents particular challenges for the VM writer. A traditional JIT solution may not offer the best performance because of cache trashing. For larger applications the interpreter may actually offer better performance than a JIT.

Over the past year I have been working on a project to improve the Java performance on these devices. I have implemented this by writing an optimised ARM Interpreter in hand crafted ARM assembler and coupling this with a Thumb2 JIT which interacts quickly and seamlessly with the interpreter.',0,0);
INSERT INTO "EVENT" VALUES(1,876,1265551200,1800,17,'Podium','English','java_davinci_vm','DaVinci VM: Where we are ? where we go ?','','This talk will report progress of the OpenJDK''s project MLVM, features already implemented and available, feature that will be soon, and some that should be implemented if YOU contribute to the project.','Each feature will be followed by a small demo (I hope :).',0,0);
INSERT INTO "EVENT" VALUES(1,877,1265553900,1800,17,'Podium','English','java_openjdk','OpenJDK Roundtable','','Discuss with OpenJDK regulars what you''re hacking on, what you''d like to do in the project, and how you''ll go about it.','',0,0);
INSERT INTO "EVENT" VALUES(1,1060,1265556600,900,17,'Podium','English','java_icedtea_plugin','IcedTea NP Plugin: the next generation Open Source Java Plugin','','Removal of OJI from Gecko has made it necessary to re-write the current IcedTea Plugin. The new IcedTea NP Plugin uses the newer, preferred NPRuntime API. It solves many of the issues surrounding the old plugin.','This talk will focus on the features of the new plugin, and it''s advantages over the old one.',0,0);
INSERT INTO "EVENT" VALUES(1,1100,1265533200,2700,32,'Podium','English','bsd_freebsd','Introduction to FreeBSD','','If you never heard of FreeBSD or want to know what it''s all about this talk is for you.','The speaker will touch topics like the differences and similarities between Linux and FreeBSD, FreeBSD''s project model and unique features which make FreeBSD a great operating system.',0,0);
INSERT INTO "EVENT" VALUES(1,1101,1265536800,2700,32,'Podium','English','bsd_newcons','The Newcons Project','','Last year I gave a talk on the state of FreeBSD''s console driver called syscons. Since then I''ve started working on a new console driver architecture for the kernel, which I''m hoping will be finished before FreeBSD 9.0.','This talk will describe how the new console driver is implemented and will highlight some of its key features, such as exclusive support for UTF-8 and reduced graphics I/O.',0,0);
INSERT INTO "EVENT" VALUES(1,1102,1265540400,2700,32,'Podium','English','bsd_autotools','Building systems with autotools and libtool','','This talk is an introduction how to create portable build systems with autotools.','The speaker will explain the required steps with an example project.

The second part is about why self-made makefiles often are worse than the auto generated ones.',0,0);
INSERT INTO "EVENT" VALUES(1,1103,1265544000,2700,32,'Podium','English','bsd_debugging','Debugging the FreeBSD kernel for dummies','','FreeBSD aims to provide a high-quality modern operating system, however adding new features inevitably introduces bugs. Although several kernel debugging tools have been added and evolved in the last years, the quality of the kernel problem reports show that only a few FreeBSD users know how (or are willing) to take advantage of them.','This talk will present the tools most commonly used when investigating problems in the kernel, some techniques to extact useful information, and the most commonly made mistakes to look for when inspecting the code. I will also give a few practical tips and examples on how not to turn kernel debugging into a frustrating experience.',0,0);
INSERT INTO "EVENT" VALUES(1,1104,1265547600,2700,32,'Podium','English','bsd_license','Because the License Matters:  BSD as the Foundation for Commercial Point of Sale Applications','','In his presentation Marc Balmer will show how and why his company micro systems choose BSD Unix and BSD licensed software as the foundation for a commercial point of sale application.','He will address economic aspects of using BSD licensed software in commercial software as well as technical challenges that had to be solved to make a stock BSD operating system run on specialised point of sale hardware.  And last, but not least, he will talk about how the BSD community at large can profit from commercial developments and what a company that uses BSD software can do to support BSD in return.',0,0);
INSERT INTO "EVENT" VALUES(1,1105,1265551200,2700,32,'Podium','English','bsd_debian','Debian GNU/kFreeBSD','','With its upcoming release Debian 6.0 aka Squeeze, for the first time, Debian users will have the choice between a Linux and a FreeBSD kernel.','Lets see what awaits the user when choosing a FreeBSD kernel.',0,0);
INSERT INTO "EVENT" VALUES(1,1106,1265554800,2700,32,'Podium','English','bsd_mercurial','Tracking FreeBSD customizations with a local Mercurial branch','','The conversion of the main FreeBSD source repository to Subversion has opened the possibility of tracking one or more FreeBSD branches closely and with a fine-grained changeset based approach.','This talk is about one of the ways the distributed Mercurial SCM can be used to periodically pull sets of changesets from the main FreeBSD svn repository and import them as atomic commits to a local branch.

Then we will describe two different ways to use the local branch as a basis for FreeBSD customizations: how to keep a stack of patches as a linear ''customization layer'' on top of FreeBSD, and how to keep another local branch with its own merge history.',0,0);
INSERT INTO "EVENT" VALUES(1,1117,1265558400,1800,32,'Podium','English','bsd_group_limit','Beyond the historical group limit in FreeBSD','','Historically FreeBSD has limited the number of groups per process (and hence per-user) to somewhere between 14 and 16 depending how you count. This leads to problems in a number of environments including the use of FreeBSD as an SMB server.','I will talk about those issues, bugs in the existing implementation, how we raised the limit to 1023 in 8.0, and what
our future plans are for group support.',0,0);
INSERT INTO "EVENT" VALUES(1,824,1265535000,5400,7,'Other','English','lpi_3','LPI exam session 3','','LPI exam session #3','',0,0);
INSERT INTO "EVENT" VALUES(1,825,1265544000,5400,7,'Other','English','lpi_4','LPI exam session 4','','LPI exam session #4','',0,0);
INSERT INTO "EVENT" VALUES(1,826,1265551200,5400,7,'Podium','English','lpi_5','LPI exam session 5','','LPI exam session #5','',0,0);
CREATE TABLE EVENT_PERSON ( xid_conference INTEGER NOT NULL
    , xid_event INTEGER NOT NULL
    , xid_person INTEGER NOT NULL
    , UNIQUE ( xid_conference , xid_event , xid_person ) ON CONFLICT REPLACE
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id)
    , FOREIGN KEY(xid_person) REFERENCES PERSON(id));
INSERT INTO "EVENT_PERSON" VALUES(1,819,46);
INSERT INTO "EVENT_PERSON" VALUES(1,803,665);
INSERT INTO "EVENT_PERSON" VALUES(1,802,664);
INSERT INTO "EVENT_PERSON" VALUES(1,809,194);
INSERT INTO "EVENT_PERSON" VALUES(1,810,670);
INSERT INTO "EVENT_PERSON" VALUES(1,808,668);
INSERT INTO "EVENT_PERSON" VALUES(1,799,661);
INSERT INTO "EVENT_PERSON" VALUES(1,797,658);
INSERT INTO "EVENT_PERSON" VALUES(1,800,662);
INSERT INTO "EVENT_PERSON" VALUES(1,832,19);
INSERT INTO "EVENT_PERSON" VALUES(1,833,678);
INSERT INTO "EVENT_PERSON" VALUES(1,834,679);
INSERT INTO "EVENT_PERSON" VALUES(1,835,680);
INSERT INTO "EVENT_PERSON" VALUES(1,864,706);
INSERT INTO "EVENT_PERSON" VALUES(1,837,682);
INSERT INTO "EVENT_PERSON" VALUES(1,838,683);
INSERT INTO "EVENT_PERSON" VALUES(1,839,684);
INSERT INTO "EVENT_PERSON" VALUES(1,840,69);
INSERT INTO "EVENT_PERSON" VALUES(1,841,52);
INSERT INTO "EVENT_PERSON" VALUES(1,842,686);
INSERT INTO "EVENT_PERSON" VALUES(1,843,702);
INSERT INTO "EVENT_PERSON" VALUES(1,844,687);
INSERT INTO "EVENT_PERSON" VALUES(1,845,688);
INSERT INTO "EVENT_PERSON" VALUES(1,846,703);
INSERT INTO "EVENT_PERSON" VALUES(1,847,704);
INSERT INTO "EVENT_PERSON" VALUES(1,848,705);
INSERT INTO "EVENT_PERSON" VALUES(1,865,707);
INSERT INTO "EVENT_PERSON" VALUES(1,1083,850);
INSERT INTO "EVENT_PERSON" VALUES(1,1093,838);
INSERT INTO "EVENT_PERSON" VALUES(1,1082,829);
INSERT INTO "EVENT_PERSON" VALUES(1,1084,756);
INSERT INTO "EVENT_PERSON" VALUES(1,1080,826);
INSERT INTO "EVENT_PERSON" VALUES(1,1086,832);
INSERT INTO "EVENT_PERSON" VALUES(1,1095,841);
INSERT INTO "EVENT_PERSON" VALUES(1,934,344);
INSERT INTO "EVENT_PERSON" VALUES(1,935,177);
INSERT INTO "EVENT_PERSON" VALUES(1,1074,747);
INSERT INTO "EVENT_PERSON" VALUES(1,1075,645);
INSERT INTO "EVENT_PERSON" VALUES(1,1075,344);
INSERT INTO "EVENT_PERSON" VALUES(1,939,645);
INSERT INTO "EVENT_PERSON" VALUES(1,939,823);
INSERT INTO "EVENT_PERSON" VALUES(1,937,640);
INSERT INTO "EVENT_PERSON" VALUES(1,828,676);
INSERT INTO "EVENT_PERSON" VALUES(1,971,334);
INSERT INTO "EVENT_PERSON" VALUES(1,972,149);
INSERT INTO "EVENT_PERSON" VALUES(1,973,339);
INSERT INTO "EVENT_PERSON" VALUES(1,974,182);
INSERT INTO "EVENT_PERSON" VALUES(1,975,761);
INSERT INTO "EVENT_PERSON" VALUES(1,961,558);
INSERT INTO "EVENT_PERSON" VALUES(1,977,764);
INSERT INTO "EVENT_PERSON" VALUES(1,977,763);
INSERT INTO "EVENT_PERSON" VALUES(1,957,51);
INSERT INTO "EVENT_PERSON" VALUES(1,958,165);
INSERT INTO "EVENT_PERSON" VALUES(1,959,292);
INSERT INTO "EVENT_PERSON" VALUES(1,1113,441);
INSERT INTO "EVENT_PERSON" VALUES(1,960,756);
INSERT INTO "EVENT_PERSON" VALUES(1,976,762);
INSERT INTO "EVENT_PERSON" VALUES(1,962,292);
INSERT INTO "EVENT_PERSON" VALUES(1,907,130);
INSERT INTO "EVENT_PERSON" VALUES(1,906,730);
INSERT INTO "EVENT_PERSON" VALUES(1,908,729);
INSERT INTO "EVENT_PERSON" VALUES(1,904,210);
INSERT INTO "EVENT_PERSON" VALUES(1,909,638);
INSERT INTO "EVENT_PERSON" VALUES(1,905,728);
INSERT INTO "EVENT_PERSON" VALUES(1,903,726);
INSERT INTO "EVENT_PERSON" VALUES(1,910,731);
INSERT INTO "EVENT_PERSON" VALUES(1,911,771);
INSERT INTO "EVENT_PERSON" VALUES(1,911,732);
INSERT INTO "EVENT_PERSON" VALUES(1,912,130);
INSERT INTO "EVENT_PERSON" VALUES(1,1061,22);
INSERT INTO "EVENT_PERSON" VALUES(1,1062,586);
INSERT INTO "EVENT_PERSON" VALUES(1,1063,22);
INSERT INTO "EVENT_PERSON" VALUES(1,1064,817);
INSERT INTO "EVENT_PERSON" VALUES(1,1064,589);
INSERT INTO "EVENT_PERSON" VALUES(1,1065,819);
INSERT INTO "EVENT_PERSON" VALUES(1,1065,818);
INSERT INTO "EVENT_PERSON" VALUES(1,1066,200);
INSERT INTO "EVENT_PERSON" VALUES(1,1067,210);
INSERT INTO "EVENT_PERSON" VALUES(1,1067,457);
INSERT INTO "EVENT_PERSON" VALUES(1,1068,588);
INSERT INTO "EVENT_PERSON" VALUES(1,1069,22);
INSERT INTO "EVENT_PERSON" VALUES(1,1070,820);
INSERT INTO "EVENT_PERSON" VALUES(1,1071,124);
INSERT INTO "EVENT_PERSON" VALUES(1,1071,821);
INSERT INTO "EVENT_PERSON" VALUES(1,1072,22);
INSERT INTO "EVENT_PERSON" VALUES(1,894,98);
INSERT INTO "EVENT_PERSON" VALUES(1,895,525);
INSERT INTO "EVENT_PERSON" VALUES(1,1079,95);
INSERT INTO "EVENT_PERSON" VALUES(1,896,725);
INSERT INTO "EVENT_PERSON" VALUES(1,897,618);
INSERT INTO "EVENT_PERSON" VALUES(1,898,147);
INSERT INTO "EVENT_PERSON" VALUES(1,899,70);
INSERT INTO "EVENT_PERSON" VALUES(1,900,725);
INSERT INTO "EVENT_PERSON" VALUES(1,1048,809);
INSERT INTO "EVENT_PERSON" VALUES(1,1054,813);
INSERT INTO "EVENT_PERSON" VALUES(1,1049,810);
INSERT INTO "EVENT_PERSON" VALUES(1,1050,811);
INSERT INTO "EVENT_PERSON" VALUES(1,1051,812);
INSERT INTO "EVENT_PERSON" VALUES(1,947,272);
INSERT INTO "EVENT_PERSON" VALUES(1,948,750);
INSERT INTO "EVENT_PERSON" VALUES(1,949,751);
INSERT INTO "EVENT_PERSON" VALUES(1,950,270);
INSERT INTO "EVENT_PERSON" VALUES(1,951,621);
INSERT INTO "EVENT_PERSON" VALUES(1,952,271);
INSERT INTO "EVENT_PERSON" VALUES(1,953,752);
INSERT INTO "EVENT_PERSON" VALUES(1,954,753);
INSERT INTO "EVENT_PERSON" VALUES(1,955,754);
INSERT INTO "EVENT_PERSON" VALUES(1,999,631);
INSERT INTO "EVENT_PERSON" VALUES(1,1000,635);
INSERT INTO "EVENT_PERSON" VALUES(1,1001,418);
INSERT INTO "EVENT_PERSON" VALUES(1,1002,406);
INSERT INTO "EVENT_PERSON" VALUES(1,1003,415);
INSERT INTO "EVENT_PERSON" VALUES(1,1004,632);
INSERT INTO "EVENT_PERSON" VALUES(1,1005,616);
INSERT INTO "EVENT_PERSON" VALUES(1,1028,795);
INSERT INTO "EVENT_PERSON" VALUES(1,1029,795);
INSERT INTO "EVENT_PERSON" VALUES(1,1030,796);
INSERT INTO "EVENT_PERSON" VALUES(1,1031,796);
INSERT INTO "EVENT_PERSON" VALUES(1,1032,797);
INSERT INTO "EVENT_PERSON" VALUES(1,1033,798);
INSERT INTO "EVENT_PERSON" VALUES(1,1056,815);
INSERT INTO "EVENT_PERSON" VALUES(1,1059,607);
INSERT INTO "EVENT_PERSON" VALUES(1,1073,822);
INSERT INTO "EVENT_PERSON" VALUES(1,1058,284);
INSERT INTO "EVENT_PERSON" VALUES(1,1057,816);
INSERT INTO "EVENT_PERSON" VALUES(1,822,42);
INSERT INTO "EVENT_PERSON" VALUES(1,823,42);
INSERT INTO "EVENT_PERSON" VALUES(1,868,293);
INSERT INTO "EVENT_PERSON" VALUES(1,869,577);
INSERT INTO "EVENT_PERSON" VALUES(1,870,567);
INSERT INTO "EVENT_PERSON" VALUES(1,871,710);
INSERT INTO "EVENT_PERSON" VALUES(1,872,711);
INSERT INTO "EVENT_PERSON" VALUES(1,829,677);
INSERT INTO "EVENT_PERSON" VALUES(1,854,692);
INSERT INTO "EVENT_PERSON" VALUES(1,867,709);
INSERT INTO "EVENT_PERSON" VALUES(1,798,660);
INSERT INTO "EVENT_PERSON" VALUES(1,801,663);
INSERT INTO "EVENT_PERSON" VALUES(1,820,675);
INSERT INTO "EVENT_PERSON" VALUES(1,804,666);
INSERT INTO "EVENT_PERSON" VALUES(1,816,673);
INSERT INTO "EVENT_PERSON" VALUES(1,817,674);
INSERT INTO "EVENT_PERSON" VALUES(1,1055,814);
INSERT INTO "EVENT_PERSON" VALUES(1,818,403);
INSERT INTO "EVENT_PERSON" VALUES(1,815,672);
INSERT INTO "EVENT_PERSON" VALUES(1,813,671);
INSERT INTO "EVENT_PERSON" VALUES(1,850,689);
INSERT INTO "EVENT_PERSON" VALUES(1,851,531);
INSERT INTO "EVENT_PERSON" VALUES(1,852,690);
INSERT INTO "EVENT_PERSON" VALUES(1,853,691);
INSERT INTO "EVENT_PERSON" VALUES(1,866,708);
INSERT INTO "EVENT_PERSON" VALUES(1,855,693);
INSERT INTO "EVENT_PERSON" VALUES(1,821,755);
INSERT INTO "EVENT_PERSON" VALUES(1,821,260);
INSERT INTO "EVENT_PERSON" VALUES(1,856,694);
INSERT INTO "EVENT_PERSON" VALUES(1,857,695);
INSERT INTO "EVENT_PERSON" VALUES(1,858,696);
INSERT INTO "EVENT_PERSON" VALUES(1,859,494);
INSERT INTO "EVENT_PERSON" VALUES(1,860,697);
INSERT INTO "EVENT_PERSON" VALUES(1,861,698);
INSERT INTO "EVENT_PERSON" VALUES(1,862,699);
INSERT INTO "EVENT_PERSON" VALUES(1,863,700);
INSERT INTO "EVENT_PERSON" VALUES(1,1089,834);
INSERT INTO "EVENT_PERSON" VALUES(1,1088,731);
INSERT INTO "EVENT_PERSON" VALUES(1,1092,837);
INSERT INTO "EVENT_PERSON" VALUES(1,1094,839);
INSERT INTO "EVENT_PERSON" VALUES(1,1081,828);
INSERT INTO "EVENT_PERSON" VALUES(1,1081,629);
INSERT INTO "EVENT_PERSON" VALUES(1,1081,827);
INSERT INTO "EVENT_PERSON" VALUES(1,1085,831);
INSERT INTO "EVENT_PERSON" VALUES(1,1091,836);
INSERT INTO "EVENT_PERSON" VALUES(1,1087,833);
INSERT INTO "EVENT_PERSON" VALUES(1,1096,843);
INSERT INTO "EVENT_PERSON" VALUES(1,1096,842);
INSERT INTO "EVENT_PERSON" VALUES(1,1090,835);
INSERT INTO "EVENT_PERSON" VALUES(1,941,745);
INSERT INTO "EVENT_PERSON" VALUES(1,941,466);
INSERT INTO "EVENT_PERSON" VALUES(1,942,746);
INSERT INTO "EVENT_PERSON" VALUES(1,943,174);
INSERT INTO "EVENT_PERSON" VALUES(1,938,261);
INSERT INTO "EVENT_PERSON" VALUES(1,936,743);
INSERT INTO "EVENT_PERSON" VALUES(1,945,180);
INSERT INTO "EVENT_PERSON" VALUES(1,1076,175);
INSERT INTO "EVENT_PERSON" VALUES(1,1077,473);
INSERT INTO "EVENT_PERSON" VALUES(1,1077,824);
INSERT INTO "EVENT_PERSON" VALUES(1,946,177);
INSERT INTO "EVENT_PERSON" VALUES(1,946,749);
INSERT INTO "EVENT_PERSON" VALUES(1,946,748);
INSERT INTO "EVENT_PERSON" VALUES(1,946,180);
INSERT INTO "EVENT_PERSON" VALUES(1,944,344);
INSERT INTO "EVENT_PERSON" VALUES(1,944,473);
INSERT INTO "EVENT_PERSON" VALUES(1,944,747);
INSERT INTO "EVENT_PERSON" VALUES(1,978,616);
INSERT INTO "EVENT_PERSON" VALUES(1,979,697);
INSERT INTO "EVENT_PERSON" VALUES(1,980,766);
INSERT INTO "EVENT_PERSON" VALUES(1,981,767);
INSERT INTO "EVENT_PERSON" VALUES(1,982,293);
INSERT INTO "EVENT_PERSON" VALUES(1,983,768);
INSERT INTO "EVENT_PERSON" VALUES(1,984,769);
INSERT INTO "EVENT_PERSON" VALUES(1,986,770);
INSERT INTO "EVENT_PERSON" VALUES(1,985,794);
INSERT INTO "EVENT_PERSON" VALUES(1,969,760);
INSERT INTO "EVENT_PERSON" VALUES(1,964,758);
INSERT INTO "EVENT_PERSON" VALUES(1,965,134);
INSERT INTO "EVENT_PERSON" VALUES(1,966,618);
INSERT INTO "EVENT_PERSON" VALUES(1,967,759);
INSERT INTO "EVENT_PERSON" VALUES(1,1116,152);
INSERT INTO "EVENT_PERSON" VALUES(1,968,187);
INSERT INTO "EVENT_PERSON" VALUES(1,963,757);
INSERT INTO "EVENT_PERSON" VALUES(1,970,74);
INSERT INTO "EVENT_PERSON" VALUES(1,913,95);
INSERT INTO "EVENT_PERSON" VALUES(1,913,130);
INSERT INTO "EVENT_PERSON" VALUES(1,914,374);
INSERT INTO "EVENT_PERSON" VALUES(1,901,457);
INSERT INTO "EVENT_PERSON" VALUES(1,1114,854);
INSERT INTO "EVENT_PERSON" VALUES(1,915,729);
INSERT INTO "EVENT_PERSON" VALUES(1,916,808);
INSERT INTO "EVENT_PERSON" VALUES(1,916,772);
INSERT INTO "EVENT_PERSON" VALUES(1,916,116);
INSERT INTO "EVENT_PERSON" VALUES(1,902,99);
INSERT INTO "EVENT_PERSON" VALUES(1,918,704);
INSERT INTO "EVENT_PERSON" VALUES(1,1078,825);
INSERT INTO "EVENT_PERSON" VALUES(1,987,774);
INSERT INTO "EVENT_PERSON" VALUES(1,987,773);
INSERT INTO "EVENT_PERSON" VALUES(1,988,775);
INSERT INTO "EVENT_PERSON" VALUES(1,989,776);
INSERT INTO "EVENT_PERSON" VALUES(1,990,30);
INSERT INTO "EVENT_PERSON" VALUES(1,991,777);
INSERT INTO "EVENT_PERSON" VALUES(1,992,774);
INSERT INTO "EVENT_PERSON" VALUES(1,993,778);
INSERT INTO "EVENT_PERSON" VALUES(1,994,779);
INSERT INTO "EVENT_PERSON" VALUES(1,995,780);
INSERT INTO "EVENT_PERSON" VALUES(1,996,781);
INSERT INTO "EVENT_PERSON" VALUES(1,997,782);
INSERT INTO "EVENT_PERSON" VALUES(1,998,774);
INSERT INTO "EVENT_PERSON" VALUES(1,998,773);
INSERT INTO "EVENT_PERSON" VALUES(1,1046,806);
INSERT INTO "EVENT_PERSON" VALUES(1,1097,845);
INSERT INTO "EVENT_PERSON" VALUES(1,1038,800);
INSERT INTO "EVENT_PERSON" VALUES(1,1039,801);
INSERT INTO "EVENT_PERSON" VALUES(1,1043,804);
INSERT INTO "EVENT_PERSON" VALUES(1,1041,803);
INSERT INTO "EVENT_PERSON" VALUES(1,1042,593);
INSERT INTO "EVENT_PERSON" VALUES(1,1040,802);
INSERT INTO "EVENT_PERSON" VALUES(1,1044,312);
INSERT INTO "EVENT_PERSON" VALUES(1,1045,805);
INSERT INTO "EVENT_PERSON" VALUES(1,1098,846);
INSERT INTO "EVENT_PERSON" VALUES(1,919,736);
INSERT INTO "EVENT_PERSON" VALUES(1,920,736);
INSERT INTO "EVENT_PERSON" VALUES(1,921,737);
INSERT INTO "EVENT_PERSON" VALUES(1,922,738);
INSERT INTO "EVENT_PERSON" VALUES(1,923,739);
INSERT INTO "EVENT_PERSON" VALUES(1,924,740);
INSERT INTO "EVENT_PERSON" VALUES(1,925,736);
INSERT INTO "EVENT_PERSON" VALUES(1,1099,797);
INSERT INTO "EVENT_PERSON" VALUES(1,926,739);
INSERT INTO "EVENT_PERSON" VALUES(1,927,741);
INSERT INTO "EVENT_PERSON" VALUES(1,928,736);
INSERT INTO "EVENT_PERSON" VALUES(1,929,736);
INSERT INTO "EVENT_PERSON" VALUES(1,930,736);
INSERT INTO "EVENT_PERSON" VALUES(1,931,742);
INSERT INTO "EVENT_PERSON" VALUES(1,932,736);
INSERT INTO "EVENT_PERSON" VALUES(1,933,736);
INSERT INTO "EVENT_PERSON" VALUES(1,1017,856);
INSERT INTO "EVENT_PERSON" VALUES(1,1021,792);
INSERT INTO "EVENT_PERSON" VALUES(1,1018,90);
INSERT INTO "EVENT_PERSON" VALUES(1,1022,793);
INSERT INTO "EVENT_PERSON" VALUES(1,1022,93);
INSERT INTO "EVENT_PERSON" VALUES(1,1023,93);
INSERT INTO "EVENT_PERSON" VALUES(1,1024,793);
INSERT INTO "EVENT_PERSON" VALUES(1,1025,793);
INSERT INTO "EVENT_PERSON" VALUES(1,1026,92);
INSERT INTO "EVENT_PERSON" VALUES(1,1027,793);
INSERT INTO "EVENT_PERSON" VALUES(1,1020,90);
INSERT INTO "EVENT_PERSON" VALUES(1,1006,783);
INSERT INTO "EVENT_PERSON" VALUES(1,1007,784);
INSERT INTO "EVENT_PERSON" VALUES(1,1008,785);
INSERT INTO "EVENT_PERSON" VALUES(1,1009,786);
INSERT INTO "EVENT_PERSON" VALUES(1,1010,787);
INSERT INTO "EVENT_PERSON" VALUES(1,1011,788);
INSERT INTO "EVENT_PERSON" VALUES(1,1012,789);
INSERT INTO "EVENT_PERSON" VALUES(1,1013,790);
INSERT INTO "EVENT_PERSON" VALUES(1,1014,722);
INSERT INTO "EVENT_PERSON" VALUES(1,1015,791);
INSERT INTO "EVENT_PERSON" VALUES(1,1016,783);
INSERT INTO "EVENT_PERSON" VALUES(1,878,713);
INSERT INTO "EVENT_PERSON" VALUES(1,879,714);
INSERT INTO "EVENT_PERSON" VALUES(1,880,715);
INSERT INTO "EVENT_PERSON" VALUES(1,881,716);
INSERT INTO "EVENT_PERSON" VALUES(1,883,717);
INSERT INTO "EVENT_PERSON" VALUES(1,884,718);
INSERT INTO "EVENT_PERSON" VALUES(1,889,694);
INSERT INTO "EVENT_PERSON" VALUES(1,886,720);
INSERT INTO "EVENT_PERSON" VALUES(1,887,721);
INSERT INTO "EVENT_PERSON" VALUES(1,888,722);
INSERT INTO "EVENT_PERSON" VALUES(1,885,719);
INSERT INTO "EVENT_PERSON" VALUES(1,891,327);
INSERT INTO "EVENT_PERSON" VALUES(1,892,723);
INSERT INTO "EVENT_PERSON" VALUES(1,890,694);
INSERT INTO "EVENT_PERSON" VALUES(1,1107,171);
INSERT INTO "EVENT_PERSON" VALUES(1,1108,851);
INSERT INTO "EVENT_PERSON" VALUES(1,1109,171);
INSERT INTO "EVENT_PERSON" VALUES(1,1110,852);
INSERT INTO "EVENT_PERSON" VALUES(1,1111,853);
INSERT INTO "EVENT_PERSON" VALUES(1,1034,467);
INSERT INTO "EVENT_PERSON" VALUES(1,1035,798);
INSERT INTO "EVENT_PERSON" VALUES(1,1036,280);
INSERT INTO "EVENT_PERSON" VALUES(1,1037,799);
INSERT INTO "EVENT_PERSON" VALUES(1,873,193);
INSERT INTO "EVENT_PERSON" VALUES(1,874,562);
INSERT INTO "EVENT_PERSON" VALUES(1,875,712);
INSERT INTO "EVENT_PERSON" VALUES(1,1047,807);
INSERT INTO "EVENT_PERSON" VALUES(1,876,567);
INSERT INTO "EVENT_PERSON" VALUES(1,877,193);
INSERT INTO "EVENT_PERSON" VALUES(1,1060,560);
INSERT INTO "EVENT_PERSON" VALUES(1,1100,416);
INSERT INTO "EVENT_PERSON" VALUES(1,1101,633);
INSERT INTO "EVENT_PERSON" VALUES(1,1102,417);
INSERT INTO "EVENT_PERSON" VALUES(1,1103,405);
INSERT INTO "EVENT_PERSON" VALUES(1,1104,632);
INSERT INTO "EVENT_PERSON" VALUES(1,1105,847);
INSERT INTO "EVENT_PERSON" VALUES(1,1106,848);
INSERT INTO "EVENT_PERSON" VALUES(1,1117,665);
INSERT INTO "EVENT_PERSON" VALUES(1,824,42);
INSERT INTO "EVENT_PERSON" VALUES(1,825,42);
INSERT INTO "EVENT_PERSON" VALUES(1,826,42);
CREATE TABLE EVENT_ROOM ( xid_conference INTEGER NOT NULL
    , xid_event INTEGER NOT NULL
    , xid_room INTEGER NOT NULL
    , UNIQUE ( xid_conference , xid_event , xid_room ) ON CONFLICT REPLACE
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id)
    , FOREIGN KEY(xid_room) REFERENCES ROOM(id));
INSERT INTO "EVENT_ROOM" VALUES(1,819,1);
INSERT INTO "EVENT_ROOM" VALUES(1,803,1);
INSERT INTO "EVENT_ROOM" VALUES(1,802,1);
INSERT INTO "EVENT_ROOM" VALUES(1,809,1);
INSERT INTO "EVENT_ROOM" VALUES(1,810,1);
INSERT INTO "EVENT_ROOM" VALUES(1,808,1);
INSERT INTO "EVENT_ROOM" VALUES(1,799,2);
INSERT INTO "EVENT_ROOM" VALUES(1,797,2);
INSERT INTO "EVENT_ROOM" VALUES(1,800,2);
INSERT INTO "EVENT_ROOM" VALUES(1,832,3);
INSERT INTO "EVENT_ROOM" VALUES(1,833,3);
INSERT INTO "EVENT_ROOM" VALUES(1,834,3);
INSERT INTO "EVENT_ROOM" VALUES(1,835,3);
INSERT INTO "EVENT_ROOM" VALUES(1,864,3);
INSERT INTO "EVENT_ROOM" VALUES(1,837,3);
INSERT INTO "EVENT_ROOM" VALUES(1,838,3);
INSERT INTO "EVENT_ROOM" VALUES(1,839,3);
INSERT INTO "EVENT_ROOM" VALUES(1,840,3);
INSERT INTO "EVENT_ROOM" VALUES(1,841,3);
INSERT INTO "EVENT_ROOM" VALUES(1,842,3);
INSERT INTO "EVENT_ROOM" VALUES(1,843,3);
INSERT INTO "EVENT_ROOM" VALUES(1,844,3);
INSERT INTO "EVENT_ROOM" VALUES(1,845,3);
INSERT INTO "EVENT_ROOM" VALUES(1,846,3);
INSERT INTO "EVENT_ROOM" VALUES(1,847,3);
INSERT INTO "EVENT_ROOM" VALUES(1,848,3);
INSERT INTO "EVENT_ROOM" VALUES(1,865,3);
INSERT INTO "EVENT_ROOM" VALUES(1,1083,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1093,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1082,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1084,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1080,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1086,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1095,4);
INSERT INTO "EVENT_ROOM" VALUES(1,934,5);
INSERT INTO "EVENT_ROOM" VALUES(1,935,5);
INSERT INTO "EVENT_ROOM" VALUES(1,1074,5);
INSERT INTO "EVENT_ROOM" VALUES(1,1075,5);
INSERT INTO "EVENT_ROOM" VALUES(1,939,5);
INSERT INTO "EVENT_ROOM" VALUES(1,937,5);
INSERT INTO "EVENT_ROOM" VALUES(1,828,6);
INSERT INTO "EVENT_ROOM" VALUES(1,971,7);
INSERT INTO "EVENT_ROOM" VALUES(1,972,7);
INSERT INTO "EVENT_ROOM" VALUES(1,973,7);
INSERT INTO "EVENT_ROOM" VALUES(1,974,7);
INSERT INTO "EVENT_ROOM" VALUES(1,975,7);
INSERT INTO "EVENT_ROOM" VALUES(1,961,7);
INSERT INTO "EVENT_ROOM" VALUES(1,977,7);
INSERT INTO "EVENT_ROOM" VALUES(1,957,8);
INSERT INTO "EVENT_ROOM" VALUES(1,958,8);
INSERT INTO "EVENT_ROOM" VALUES(1,959,8);
INSERT INTO "EVENT_ROOM" VALUES(1,1113,8);
INSERT INTO "EVENT_ROOM" VALUES(1,960,8);
INSERT INTO "EVENT_ROOM" VALUES(1,976,8);
INSERT INTO "EVENT_ROOM" VALUES(1,962,8);
INSERT INTO "EVENT_ROOM" VALUES(1,907,9);
INSERT INTO "EVENT_ROOM" VALUES(1,906,9);
INSERT INTO "EVENT_ROOM" VALUES(1,908,9);
INSERT INTO "EVENT_ROOM" VALUES(1,904,9);
INSERT INTO "EVENT_ROOM" VALUES(1,909,9);
INSERT INTO "EVENT_ROOM" VALUES(1,905,9);
INSERT INTO "EVENT_ROOM" VALUES(1,903,9);
INSERT INTO "EVENT_ROOM" VALUES(1,910,9);
INSERT INTO "EVENT_ROOM" VALUES(1,911,9);
INSERT INTO "EVENT_ROOM" VALUES(1,912,9);
INSERT INTO "EVENT_ROOM" VALUES(1,1061,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1062,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1063,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1064,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1065,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1066,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1067,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1068,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1069,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1070,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1071,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1072,10);
INSERT INTO "EVENT_ROOM" VALUES(1,894,11);
INSERT INTO "EVENT_ROOM" VALUES(1,895,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1079,11);
INSERT INTO "EVENT_ROOM" VALUES(1,896,11);
INSERT INTO "EVENT_ROOM" VALUES(1,897,11);
INSERT INTO "EVENT_ROOM" VALUES(1,898,11);
INSERT INTO "EVENT_ROOM" VALUES(1,899,11);
INSERT INTO "EVENT_ROOM" VALUES(1,900,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1048,12);
INSERT INTO "EVENT_ROOM" VALUES(1,1054,12);
INSERT INTO "EVENT_ROOM" VALUES(1,1049,12);
INSERT INTO "EVENT_ROOM" VALUES(1,1050,12);
INSERT INTO "EVENT_ROOM" VALUES(1,1051,12);
INSERT INTO "EVENT_ROOM" VALUES(1,947,13);
INSERT INTO "EVENT_ROOM" VALUES(1,948,13);
INSERT INTO "EVENT_ROOM" VALUES(1,949,13);
INSERT INTO "EVENT_ROOM" VALUES(1,950,13);
INSERT INTO "EVENT_ROOM" VALUES(1,951,13);
INSERT INTO "EVENT_ROOM" VALUES(1,952,13);
INSERT INTO "EVENT_ROOM" VALUES(1,953,13);
INSERT INTO "EVENT_ROOM" VALUES(1,954,13);
INSERT INTO "EVENT_ROOM" VALUES(1,955,13);
INSERT INTO "EVENT_ROOM" VALUES(1,999,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1000,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1001,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1002,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1003,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1004,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1005,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1028,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1029,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1030,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1031,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1032,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1033,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1056,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1059,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1073,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1058,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1057,16);
INSERT INTO "EVENT_ROOM" VALUES(1,822,17);
INSERT INTO "EVENT_ROOM" VALUES(1,823,17);
INSERT INTO "EVENT_ROOM" VALUES(1,868,18);
INSERT INTO "EVENT_ROOM" VALUES(1,869,18);
INSERT INTO "EVENT_ROOM" VALUES(1,870,18);
INSERT INTO "EVENT_ROOM" VALUES(1,871,18);
INSERT INTO "EVENT_ROOM" VALUES(1,872,18);
INSERT INTO "EVENT_ROOM" VALUES(1,829,1);
INSERT INTO "EVENT_ROOM" VALUES(1,854,1);
INSERT INTO "EVENT_ROOM" VALUES(1,867,1);
INSERT INTO "EVENT_ROOM" VALUES(1,798,1);
INSERT INTO "EVENT_ROOM" VALUES(1,801,1);
INSERT INTO "EVENT_ROOM" VALUES(1,820,1);
INSERT INTO "EVENT_ROOM" VALUES(1,804,1);
INSERT INTO "EVENT_ROOM" VALUES(1,816,2);
INSERT INTO "EVENT_ROOM" VALUES(1,817,2);
INSERT INTO "EVENT_ROOM" VALUES(1,1055,2);
INSERT INTO "EVENT_ROOM" VALUES(1,818,2);
INSERT INTO "EVENT_ROOM" VALUES(1,815,2);
INSERT INTO "EVENT_ROOM" VALUES(1,813,2);
INSERT INTO "EVENT_ROOM" VALUES(1,850,3);
INSERT INTO "EVENT_ROOM" VALUES(1,851,3);
INSERT INTO "EVENT_ROOM" VALUES(1,852,3);
INSERT INTO "EVENT_ROOM" VALUES(1,853,3);
INSERT INTO "EVENT_ROOM" VALUES(1,866,3);
INSERT INTO "EVENT_ROOM" VALUES(1,855,3);
INSERT INTO "EVENT_ROOM" VALUES(1,821,3);
INSERT INTO "EVENT_ROOM" VALUES(1,856,3);
INSERT INTO "EVENT_ROOM" VALUES(1,857,3);
INSERT INTO "EVENT_ROOM" VALUES(1,858,3);
INSERT INTO "EVENT_ROOM" VALUES(1,859,3);
INSERT INTO "EVENT_ROOM" VALUES(1,860,3);
INSERT INTO "EVENT_ROOM" VALUES(1,861,3);
INSERT INTO "EVENT_ROOM" VALUES(1,862,3);
INSERT INTO "EVENT_ROOM" VALUES(1,863,3);
INSERT INTO "EVENT_ROOM" VALUES(1,1089,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1088,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1092,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1094,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1081,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1085,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1091,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1087,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1096,4);
INSERT INTO "EVENT_ROOM" VALUES(1,1090,4);
INSERT INTO "EVENT_ROOM" VALUES(1,941,5);
INSERT INTO "EVENT_ROOM" VALUES(1,942,5);
INSERT INTO "EVENT_ROOM" VALUES(1,943,5);
INSERT INTO "EVENT_ROOM" VALUES(1,938,5);
INSERT INTO "EVENT_ROOM" VALUES(1,936,5);
INSERT INTO "EVENT_ROOM" VALUES(1,945,5);
INSERT INTO "EVENT_ROOM" VALUES(1,1076,5);
INSERT INTO "EVENT_ROOM" VALUES(1,1077,5);
INSERT INTO "EVENT_ROOM" VALUES(1,946,5);
INSERT INTO "EVENT_ROOM" VALUES(1,944,5);
INSERT INTO "EVENT_ROOM" VALUES(1,978,7);
INSERT INTO "EVENT_ROOM" VALUES(1,979,7);
INSERT INTO "EVENT_ROOM" VALUES(1,980,7);
INSERT INTO "EVENT_ROOM" VALUES(1,981,7);
INSERT INTO "EVENT_ROOM" VALUES(1,982,7);
INSERT INTO "EVENT_ROOM" VALUES(1,983,7);
INSERT INTO "EVENT_ROOM" VALUES(1,984,7);
INSERT INTO "EVENT_ROOM" VALUES(1,986,7);
INSERT INTO "EVENT_ROOM" VALUES(1,985,7);
INSERT INTO "EVENT_ROOM" VALUES(1,969,8);
INSERT INTO "EVENT_ROOM" VALUES(1,964,8);
INSERT INTO "EVENT_ROOM" VALUES(1,965,8);
INSERT INTO "EVENT_ROOM" VALUES(1,966,8);
INSERT INTO "EVENT_ROOM" VALUES(1,967,8);
INSERT INTO "EVENT_ROOM" VALUES(1,1116,8);
INSERT INTO "EVENT_ROOM" VALUES(1,968,8);
INSERT INTO "EVENT_ROOM" VALUES(1,963,8);
INSERT INTO "EVENT_ROOM" VALUES(1,970,8);
INSERT INTO "EVENT_ROOM" VALUES(1,913,9);
INSERT INTO "EVENT_ROOM" VALUES(1,914,9);
INSERT INTO "EVENT_ROOM" VALUES(1,901,9);
INSERT INTO "EVENT_ROOM" VALUES(1,1114,9);
INSERT INTO "EVENT_ROOM" VALUES(1,915,9);
INSERT INTO "EVENT_ROOM" VALUES(1,916,9);
INSERT INTO "EVENT_ROOM" VALUES(1,902,9);
INSERT INTO "EVENT_ROOM" VALUES(1,918,9);
INSERT INTO "EVENT_ROOM" VALUES(1,1078,9);
INSERT INTO "EVENT_ROOM" VALUES(1,987,10);
INSERT INTO "EVENT_ROOM" VALUES(1,988,10);
INSERT INTO "EVENT_ROOM" VALUES(1,989,10);
INSERT INTO "EVENT_ROOM" VALUES(1,990,10);
INSERT INTO "EVENT_ROOM" VALUES(1,991,10);
INSERT INTO "EVENT_ROOM" VALUES(1,992,10);
INSERT INTO "EVENT_ROOM" VALUES(1,993,10);
INSERT INTO "EVENT_ROOM" VALUES(1,994,10);
INSERT INTO "EVENT_ROOM" VALUES(1,995,10);
INSERT INTO "EVENT_ROOM" VALUES(1,996,10);
INSERT INTO "EVENT_ROOM" VALUES(1,997,10);
INSERT INTO "EVENT_ROOM" VALUES(1,998,10);
INSERT INTO "EVENT_ROOM" VALUES(1,1046,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1097,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1038,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1039,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1043,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1041,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1042,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1040,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1044,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1045,11);
INSERT INTO "EVENT_ROOM" VALUES(1,1098,11);
INSERT INTO "EVENT_ROOM" VALUES(1,919,12);
INSERT INTO "EVENT_ROOM" VALUES(1,920,12);
INSERT INTO "EVENT_ROOM" VALUES(1,921,12);
INSERT INTO "EVENT_ROOM" VALUES(1,922,12);
INSERT INTO "EVENT_ROOM" VALUES(1,923,12);
INSERT INTO "EVENT_ROOM" VALUES(1,924,12);
INSERT INTO "EVENT_ROOM" VALUES(1,925,12);
INSERT INTO "EVENT_ROOM" VALUES(1,1099,12);
INSERT INTO "EVENT_ROOM" VALUES(1,926,12);
INSERT INTO "EVENT_ROOM" VALUES(1,927,12);
INSERT INTO "EVENT_ROOM" VALUES(1,928,12);
INSERT INTO "EVENT_ROOM" VALUES(1,929,12);
INSERT INTO "EVENT_ROOM" VALUES(1,930,12);
INSERT INTO "EVENT_ROOM" VALUES(1,931,12);
INSERT INTO "EVENT_ROOM" VALUES(1,932,12);
INSERT INTO "EVENT_ROOM" VALUES(1,933,12);
INSERT INTO "EVENT_ROOM" VALUES(1,1017,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1021,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1018,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1022,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1023,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1024,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1025,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1026,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1027,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1020,19);
INSERT INTO "EVENT_ROOM" VALUES(1,1006,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1007,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1008,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1009,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1010,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1011,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1012,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1013,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1014,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1015,13);
INSERT INTO "EVENT_ROOM" VALUES(1,1016,13);
INSERT INTO "EVENT_ROOM" VALUES(1,878,14);
INSERT INTO "EVENT_ROOM" VALUES(1,879,14);
INSERT INTO "EVENT_ROOM" VALUES(1,880,14);
INSERT INTO "EVENT_ROOM" VALUES(1,881,14);
INSERT INTO "EVENT_ROOM" VALUES(1,883,14);
INSERT INTO "EVENT_ROOM" VALUES(1,884,14);
INSERT INTO "EVENT_ROOM" VALUES(1,889,14);
INSERT INTO "EVENT_ROOM" VALUES(1,886,14);
INSERT INTO "EVENT_ROOM" VALUES(1,887,14);
INSERT INTO "EVENT_ROOM" VALUES(1,888,14);
INSERT INTO "EVENT_ROOM" VALUES(1,885,14);
INSERT INTO "EVENT_ROOM" VALUES(1,891,14);
INSERT INTO "EVENT_ROOM" VALUES(1,892,14);
INSERT INTO "EVENT_ROOM" VALUES(1,890,14);
INSERT INTO "EVENT_ROOM" VALUES(1,1107,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1108,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1109,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1110,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1111,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1034,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1035,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1036,15);
INSERT INTO "EVENT_ROOM" VALUES(1,1037,15);
INSERT INTO "EVENT_ROOM" VALUES(1,873,20);
INSERT INTO "EVENT_ROOM" VALUES(1,874,20);
INSERT INTO "EVENT_ROOM" VALUES(1,875,20);
INSERT INTO "EVENT_ROOM" VALUES(1,1047,20);
INSERT INTO "EVENT_ROOM" VALUES(1,876,20);
INSERT INTO "EVENT_ROOM" VALUES(1,877,20);
INSERT INTO "EVENT_ROOM" VALUES(1,1060,20);
INSERT INTO "EVENT_ROOM" VALUES(1,1100,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1101,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1102,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1103,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1104,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1105,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1106,16);
INSERT INTO "EVENT_ROOM" VALUES(1,1117,16);
INSERT INTO "EVENT_ROOM" VALUES(1,824,17);
INSERT INTO "EVENT_ROOM" VALUES(1,825,17);
INSERT INTO "EVENT_ROOM" VALUES(1,826,17);
CREATE TABLE LINK ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL
    , xid_conference INTEGER NOT NULL
    , xid_event INTEGER NOT NULL
    , name VARCHAR
    , url VARCHAR NOT NULL
    , UNIQUE ( xid_conference , xid_event , url ) ON CONFLICT REPLACE
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id));
INSERT INTO "LINK" VALUES(1421,1,809,'Homepage','http://sourceware.org/systemtap/');
INSERT INTO "LINK" VALUES(1422,1,808,'Flapjack','http://flapjack-project.com/');
INSERT INTO "LINK" VALUES(1423,1,808,'cucumber-nagios','http://auxesis.github.com/cucumber-nagios');
INSERT INTO "LINK" VALUES(1424,1,797,'Official Website','http://nmap.org');
INSERT INTO "LINK" VALUES(1425,1,797,'NSF Chapters from the Nmap book','http://nmap.org/book/nse.html');
INSERT INTO "LINK" VALUES(1426,1,832,'http://fosdem.org','http://fosdem.org');
INSERT INTO "LINK" VALUES(1427,1,833,'http://www.muenchen.de/limux','http://www.muenchen.de/limux');
INSERT INTO "LINK" VALUES(1428,1,834,'http://www.civicrm.org','http://www.civicrm.org');
INSERT INTO "LINK" VALUES(1429,1,835,'http://portableapps.com','http://portableapps.com');
INSERT INTO "LINK" VALUES(1430,1,864,'http://www.openpcf.org/','http://www.openpcf.org/');
INSERT INTO "LINK" VALUES(1431,1,837,'http://savannah.gnu.org/','http://savannah.gnu.org/');
INSERT INTO "LINK" VALUES(1432,1,838,'http://www.qi-hardware.com','http://www.qi-hardware.com');
INSERT INTO "LINK" VALUES(1433,1,839,'http://tinc-vpn.org/','http://tinc-vpn.org/');
INSERT INTO "LINK" VALUES(1434,1,840,'http://beernet.info.ucl.ac.be','http://beernet.info.ucl.ac.be');
INSERT INTO "LINK" VALUES(1435,1,841,'http://sip-communicator.org','http://sip-communicator.org');
INSERT INTO "LINK" VALUES(1436,1,842,'http://www.kamailio.org','http://www.kamailio.org');
INSERT INTO "LINK" VALUES(1437,1,843,'http://asterisk.org','http://asterisk.org');
INSERT INTO "LINK" VALUES(1438,1,844,'http://www.csync.org/','http://www.csync.org/');
INSERT INTO "LINK" VALUES(1439,1,845,'http://faban.sunsource.net','http://faban.sunsource.net');
INSERT INTO "LINK" VALUES(1440,1,846,'http://www.shadowcircle.org','http://www.shadowcircle.org');
INSERT INTO "LINK" VALUES(1441,1,847,'http://syncevolution.org','http://syncevolution.org');
INSERT INTO "LINK" VALUES(1442,1,848,'http://www.geexbox.org/','http://www.geexbox.org/');
INSERT INTO "LINK" VALUES(1443,1,865,'http://www.uzbl.org','http://www.uzbl.org');
INSERT INTO "LINK" VALUES(1444,1,1080,'http://barebox.org','http://barebox.org');
INSERT INTO "LINK" VALUES(1445,1,971,'http://en.opensuse.org/Hermes','http://en.opensuse.org/Hermes');
INSERT INTO "LINK" VALUES(1446,1,972,'http://en.opensuse.org/YaST','http://en.opensuse.org/YaST');
INSERT INTO "LINK" VALUES(1447,1,973,'http://mirrorbrain.org/','http://mirrorbrain.org/');
INSERT INTO "LINK" VALUES(1448,1,1113,'http://github.com/mmeeks/bootchart','http://github.com/mmeeks/bootchart');
INSERT INTO "LINK" VALUES(1449,1,903,'Project site','http://www.softnet.tuc.gr/~whoneedselta/misha/');
INSERT INTO "LINK" VALUES(1450,1,903,'Video presentation','http://www.softnet.tuc.gr/~whoneedselta/misha/video/flowplayer/play/');
INSERT INTO "LINK" VALUES(1451,1,900,'http://es.kde.org/','http://es.kde.org/');
INSERT INTO "LINK" VALUES(1452,1,1050,'JAIN SLEE','http://www.jainslee.org/');
INSERT INTO "LINK" VALUES(1453,1,1050,'JSR-240','http://jcp.org/en/jsr/detail?id=240');
INSERT INTO "LINK" VALUES(1454,1,1050,'NgIN','http://en.wikipedia.org/wiki/NGIN');
INSERT INTO "LINK" VALUES(1455,1,1050,'IMS','http://en.wikipedia.org/wiki/IP_Multimedia_Subsystem');
INSERT INTO "LINK" VALUES(1456,1,1050,'Mobicents','http://www.mobicents.org/');
INSERT INTO "LINK" VALUES(1457,1,947,'http://extensions.openoffice.org/','http://extensions.openoffice.org/');
INSERT INTO "LINK" VALUES(1458,1,947,'http://extensions.services.openoffice.org','http://extensions.services.openoffice.org');
INSERT INTO "LINK" VALUES(1459,1,947,'http://wiki.services.openoffice.org/wiki/Extensions','http://wiki.services.openoffice.org/wiki/Extensions');
INSERT INTO "LINK" VALUES(1460,1,948,'http://wiki.services.openoffice.org/wiki/Framework','http://wiki.services.openoffice.org/wiki/Framework');
INSERT INTO "LINK" VALUES(1461,1,949,'http://blogs.sun.com/GullFOSS/entry/building_openoffice_org_with_gnu','http://blogs.sun.com/GullFOSS/entry/building_openoffice_org_with_gnu');
INSERT INTO "LINK" VALUES(1462,1,949,'http://blogs.sun.com/GullFOSS/entry/build_scalability1','http://blogs.sun.com/GullFOSS/entry/build_scalability1');
INSERT INTO "LINK" VALUES(1463,1,949,'http://blogs.sun.com/GullFOSS/entry/a_split_build_for_openoffice','http://blogs.sun.com/GullFOSS/entry/a_split_build_for_openoffice');
INSERT INTO "LINK" VALUES(1464,1,949,'http://wiki.services.openoffice.org/wiki/Build_Environment_Effort','http://wiki.services.openoffice.org/wiki/Build_Environment_Effort');
INSERT INTO "LINK" VALUES(1465,1,952,'http://blog.thebehrens.net/2008/09/29/ooo-non-vision/','http://blog.thebehrens.net/2008/09/29/ooo-non-vision/');
INSERT INTO "LINK" VALUES(1466,1,954,'http://odftoolkit.org/projects/odfdom/pages/Home','http://odftoolkit.org/projects/odfdom/pages/Home');
INSERT INTO "LINK" VALUES(1467,1,1028,'http://coreboot.org','http://coreboot.org');
INSERT INTO "LINK" VALUES(1468,1,1057,'http://cbac.rubyforge.org/intro.html','http://cbac.rubyforge.org/intro.html');
INSERT INTO "LINK" VALUES(1469,1,868,'http://wiki.debian.org/Java/DevJam/2010/FosdemProposedTalks/JavaPackaging','http://wiki.debian.org/Java/DevJam/2010/FosdemProposedTalks/JavaPackaging');
INSERT INTO "LINK" VALUES(1470,1,870,'Project Lambda','http://openjdk.java.net/projects/lambda');
INSERT INTO "LINK" VALUES(1471,1,870,'MLVM','http://openjdk.java.net/projects/mlvm');
INSERT INTO "LINK" VALUES(1472,1,871,'http://wizard4j.org/','http://wizard4j.org/');
INSERT INTO "LINK" VALUES(1473,1,872,'http://www.playframework.org/','http://www.playframework.org/');
INSERT INTO "LINK" VALUES(1474,1,829,'RepRap','http://reprap.org/bin/view/Main/PressPix');
INSERT INTO "LINK" VALUES(1475,1,854,'https://torproject.org/','https://torproject.org/');
INSERT INTO "LINK" VALUES(1476,1,820,'identi.ca','http://identi.ca');
INSERT INTO "LINK" VALUES(1477,1,820,'StatusNet','http://status.net');
INSERT INTO "LINK" VALUES(1478,1,850,'http://www.kerrighed.org','http://www.kerrighed.org');
INSERT INTO "LINK" VALUES(1479,1,851,'http://incubator.apache.org/ace/','http://incubator.apache.org/ace/');
INSERT INTO "LINK" VALUES(1480,1,852,'http://bitbucket.org/dotcloud/cloudlets','http://bitbucket.org/dotcloud/cloudlets');
INSERT INTO "LINK" VALUES(1481,1,853,'http://www.webtoolkit.eu/wt/blog/2009/11/26/wt__dbo__an_orm__c___style','http://www.webtoolkit.eu/wt/blog/2009/11/26/wt__dbo__an_orm__c___style');
INSERT INTO "LINK" VALUES(1482,1,866,'http://openerp.com','http://openerp.com');
INSERT INTO "LINK" VALUES(1483,1,855,'http://www.cacert.org/','http://www.cacert.org/');
INSERT INTO "LINK" VALUES(1484,1,856,'http://mysql.org','http://mysql.org');
INSERT INTO "LINK" VALUES(1485,1,857,'http://kaizendo.org/','http://kaizendo.org/');
INSERT INTO "LINK" VALUES(1486,1,858,'http://thewiki4opentech.org','http://thewiki4opentech.org');
INSERT INTO "LINK" VALUES(1487,1,859,'http://www.bluedust.dontexist.com/qubit/','http://www.bluedust.dontexist.com/qubit/');
INSERT INTO "LINK" VALUES(1488,1,860,'http://padre.perlide.org/','http://padre.perlide.org/');
INSERT INTO "LINK" VALUES(1489,1,861,'http://coccinelle.lip6.fr','http://coccinelle.lip6.fr');
INSERT INTO "LINK" VALUES(1490,1,862,'http://umlcanvas.org','http://umlcanvas.org');
INSERT INTO "LINK" VALUES(1491,1,863,'http://jspoker.pokersource.info','http://jspoker.pokersource.info');
INSERT INTO "LINK" VALUES(1492,1,1088,'SeriesFinale demo','http://www.joaquimrocha.com/2009/12/06/seriesfinale/');
INSERT INTO "LINK" VALUES(1493,1,943,'https://wiki.mozilla.org/L20n','https://wiki.mozilla.org/L20n');
INSERT INTO "LINK" VALUES(1494,1,936,'http://www.womoz.org/blog/?p=231','http://www.womoz.org/blog/?p=231');
INSERT INTO "LINK" VALUES(1495,1,980,'Config::Model project site','http://config-model.wiki.sourceforge.net/');
INSERT INTO "LINK" VALUES(1496,1,980,'Package upgrade with Config::Model for Debian','http://wiki.debian.org/PackageConfigUpgrade');
INSERT INTO "LINK" VALUES(1497,1,980,'Config::Model on CPAN','http://search.cpan.org/~ddumont/');
INSERT INTO "LINK" VALUES(1498,1,981,'http://nixos.org/','http://nixos.org/');
INSERT INTO "LINK" VALUES(1499,1,984,'http://en.opensuse.org/Build_Service/KIWI','http://en.opensuse.org/Build_Service/KIWI');
INSERT INTO "LINK" VALUES(1500,1,984,'http://kiwi.berlios.de/','http://kiwi.berlios.de/');
INSERT INTO "LINK" VALUES(1501,1,986,'http://sourceforge.net/projects/dracut/','http://sourceforge.net/projects/dracut/');
INSERT INTO "LINK" VALUES(1502,1,986,'https://apps.sourceforge.net/trac/dracut/wiki','https://apps.sourceforge.net/trac/dracut/wiki');
INSERT INTO "LINK" VALUES(1503,1,986,'http://dracut.git.sourceforge.net/','http://dracut.git.sourceforge.net/');
INSERT INTO "LINK" VALUES(1504,1,986,'https://fedoraproject.org/wiki/Dracut','https://fedoraproject.org/wiki/Dracut');
INSERT INTO "LINK" VALUES(1505,1,985,'http://susestudio.com/','http://susestudio.com/');
INSERT INTO "LINK" VALUES(1506,1,985,'http://en.opensuse.org/SUSE_Studio','http://en.opensuse.org/SUSE_Studio');
INSERT INTO "LINK" VALUES(1507,1,969,'MANCOOSI project','http://www.mancoosi.org/');
INSERT INTO "LINK" VALUES(1508,1,969,'Caixa Mágica','http://www.caixamagica.pt/');
INSERT INTO "LINK" VALUES(1509,1,901,'http://coherence-project.org/','http://coherence-project.org/');
INSERT INTO "LINK" VALUES(1510,1,1114,'https://launchpad.net/desktopcouch','https://launchpad.net/desktopcouch');
INSERT INTO "LINK" VALUES(1511,1,1114,'http://www.freedesktop.org/wiki/Specifications/desktopcouch','http://www.freedesktop.org/wiki/Specifications/desktopcouch');
INSERT INTO "LINK" VALUES(1512,1,1114,'http://www.understated.co.uk/2009/starting-out-with-desktop-couch/','http://www.understated.co.uk/2009/starting-out-with-desktop-couch/');
INSERT INTO "LINK" VALUES(1513,1,916,'Solang','http://projects.gnome.org/solang');
INSERT INTO "LINK" VALUES(1514,1,916,'FSter','http://gitorious.org/itsme/fster');
INSERT INTO "LINK" VALUES(1515,1,916,'Daily Catchup','http://labs.codethink.co.uk');
INSERT INTO "LINK" VALUES(1516,1,916,'Gnome Activity Journal','http://seilo.geekyogre.com/2010/01/gaj-not-just-mockups/');
INSERT INTO "LINK" VALUES(1517,1,1097,'http://drupal.org/project/views','http://drupal.org/project/views');
INSERT INTO "LINK" VALUES(1518,1,1098,'http://www.slideshare.net/kvantomme/semantic-web-and-drupal-an-introduction','http://www.slideshare.net/kvantomme/semantic-web-and-drupal-an-introduction');
INSERT INTO "LINK" VALUES(1519,1,920,'http://code.google.com/p/rosetta-os/','http://code.google.com/p/rosetta-os/');
INSERT INTO "LINK" VALUES(1520,1,921,'http://www.rtems.org','http://www.rtems.org');
INSERT INTO "LINK" VALUES(1521,1,922,'http://www.haiku-os.org/','http://www.haiku-os.org/');
INSERT INTO "LINK" VALUES(1522,1,923,'http://hurd.gnu.org/','http://hurd.gnu.org/');
INSERT INTO "LINK" VALUES(1523,1,924,'http://hub.opensolaris.org/bin/view/Project+crossbow/','http://hub.opensolaris.org/bin/view/Project+crossbow/');
INSERT INTO "LINK" VALUES(1524,1,925,'http://wiki.freedesktop.org/wiki/Software/gallium','http://wiki.freedesktop.org/wiki/Software/gallium');
INSERT INTO "LINK" VALUES(1525,1,925,'http://aros.sourceforge.net/','http://aros.sourceforge.net/');
INSERT INTO "LINK" VALUES(1526,1,925,'http://www.haiku-os.org/','http://www.haiku-os.org/');
INSERT INTO "LINK" VALUES(1527,1,926,'http://www.kgi-project.org','http://www.kgi-project.org');
INSERT INTO "LINK" VALUES(1528,1,926,'http://hurd.gnu.org','http://hurd.gnu.org');
INSERT INTO "LINK" VALUES(1529,1,927,'TUD:OS','http://os.inf.tu-dresden.de');
INSERT INTO "LINK" VALUES(1530,1,927,'Genode','http://genode.org');
INSERT INTO "LINK" VALUES(1531,1,927,'Genode Labs','http://www.genode-labs.com/');
INSERT INTO "LINK" VALUES(1532,1,927,'Minix 3','http://www.minix3.org');
INSERT INTO "LINK" VALUES(1533,1,928,'http://developer.opensound.com/','http://developer.opensound.com/');
INSERT INTO "LINK" VALUES(1534,1,928,'http://www.haiku-os.org/','http://www.haiku-os.org/');
INSERT INTO "LINK" VALUES(1535,1,931,'http://www.haiku-os.org/','http://www.haiku-os.org/');
INSERT INTO "LINK" VALUES(1536,1,1017,'http://www.gnustep.org/','http://www.gnustep.org/');
INSERT INTO "LINK" VALUES(1537,1,1017,'http://wiki.gnustep.org/index.php/FOSDEM_2010','http://wiki.gnustep.org/index.php/FOSDEM_2010');
INSERT INTO "LINK" VALUES(1538,1,1021,'http://www.gnustep.org/','http://www.gnustep.org/');
INSERT INTO "LINK" VALUES(1539,1,1021,'http://wiki.gnustep.org/index.php/Gui','http://wiki.gnustep.org/index.php/Gui');
INSERT INTO "LINK" VALUES(1540,1,1021,'http://gnustep.org/resources/documentation/Developer/Gui/ReleaseNotes/ReleaseNotes.html','http://gnustep.org/resources/documentation/Developer/Gui/ReleaseNotes/ReleaseNotes.html');
INSERT INTO "LINK" VALUES(1541,1,1018,'http://wiki.gnustep.org/index.php/SimpleWebKit','http://wiki.gnustep.org/index.php/SimpleWebKit');
INSERT INTO "LINK" VALUES(1542,1,1022,'http://www.etoileos.com/','http://www.etoileos.com/');
INSERT INTO "LINK" VALUES(1543,1,1023,'EtoileUI overview','http://www.etoileos.com/etoile/features/etoileui');
INSERT INTO "LINK" VALUES(1544,1,1023,'Étoilé website','http://www.etoileos.com/');
INSERT INTO "LINK" VALUES(1545,1,1024,'Étoilé website','http://www.etoileos.com/');
INSERT INTO "LINK" VALUES(1546,1,1024,'clang','http://clang.llvm.org/');
INSERT INTO "LINK" VALUES(1547,1,1025,'Étoilé website','http://www.etoileos.com/');
INSERT INTO "LINK" VALUES(1548,1,1025,'Étoilé roadmap','http://etoileos.com/dev/roadmap/');
INSERT INTO "LINK" VALUES(1549,1,1026,'Étoilé website','http://www.etoileos.com/');
INSERT INTO "LINK" VALUES(1550,1,1020,'http://developer.apple.com/leopard/overview/objectivec2.html','http://developer.apple.com/leopard/overview/objectivec2.html');
INSERT INTO "LINK" VALUES(1551,1,1020,'http://www.quantum-step.com/download/sources/mySTEP/ocpp-2.0','http://www.quantum-step.com/download/sources/mySTEP/ocpp-2.0');
INSERT INTO "LINK" VALUES(1552,1,1008,'http://www.mongodb.org/','http://www.mongodb.org/');
INSERT INTO "LINK" VALUES(1553,1,1009,'http://hadoop.apache.org/hbase/','http://hadoop.apache.org/hbase/');
INSERT INTO "LINK" VALUES(1554,1,878,'http://www.phpmyadmin.net/','http://www.phpmyadmin.net/');
INSERT INTO "LINK" VALUES(1555,1,881,'Drizzle','https://launchpad.net/drizzle');
INSERT INTO "LINK" VALUES(1556,1,883,'https://launchpad.net/codership-mysql/','https://launchpad.net/codership-mysql/');
INSERT INTO "LINK" VALUES(1557,1,888,'http://www.maatkit.org/','http://www.maatkit.org/');
INSERT INTO "LINK" VALUES(1558,1,874,'https://gervill.dev.java.net/','https://gervill.dev.java.net/');
INSERT INTO "LINK" VALUES(1559,1,875,'http://www.webtoolkit.eu/jwt','http://www.webtoolkit.eu/jwt');
INSERT INTO "LINK" VALUES(1560,1,1047,'http://mint.camswl.com/openjdk.htm','http://mint.camswl.com/openjdk.htm');
INSERT INTO "LINK" VALUES(1561,1,876,'http://openjdk.java.net/projects/mlvm','http://openjdk.java.net/projects/mlvm');
INSERT INTO "LINK" VALUES(1562,1,1105,'http://noone.org/talks/kfreebsd/','http://noone.org/talks/kfreebsd/');
DELETE FROM sqlite_sequence;
INSERT INTO "sqlite_sequence" VALUES('CONFERENCE',1);
INSERT INTO "sqlite_sequence" VALUES('ROOM',20);
INSERT INTO "sqlite_sequence" VALUES('TRACK',32);
INSERT INTO "sqlite_sequence" VALUES('LINK',1562);
COMMIT;
