#------------------------------------------------------------
#        Script MySQL.
#------------------------------------------------------------

/* Dropping existing tables */

DROP TABLE IF EXISTS Tour;
DROP TABLE IF EXISTS Routes;
DROP TABLE IF EXISTS Localiser;
DROP TABLE IF EXISTS Coordonnees;
DROP TABLE IF EXISTS Quartiers;
DROP TABLE IF EXISTS Commune;
DROP TABLE IF EXISTS Partie;
DROP TABLE IF EXISTS Joueuses;
DROP TABLE IF EXISTS IncImage;
DROP TABLE IF EXISTS Image;
DROP TABLE IF EXISTS Configuration;

#------------------------------------------------------------
# Table: Commune
#------------------------------------------------------------

CREATE TABLE Commune(
        CP          Int NOT NULL,
        nomC        Text NOT NULL,
        departement Text NOT NULL,
		CONSTRAINT Commune_PK PRIMARY KEY (CP)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Quartiers
#------------------------------------------------------------

CREATE TABLE Quartiers(
        idQ              Int NOT NULL,
        nomQ             Text NOT NULL,
        codeInsee        Int NOT NULL,
        typeQ            Char (1) NOT NULL,
        CP               Int NOT NULL,
		CONSTRAINT Quartiers_PK PRIMARY KEY (idQ),
		CONSTRAINT Quartiers_Commune_FK FOREIGN KEY (CP) REFERENCES Commune(CP)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Joueuses
#------------------------------------------------------------

CREATE TABLE Joueuses(
        idJ    Int NOT NULL,
        nomJ   Text NOT NULL,
        emailJ Text NOT NULL,
		CONSTRAINT Joueuses_PK PRIMARY KEY (idJ)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Configuration
#------------------------------------------------------------

CREATE TABLE Configuration(
        idConf        Int AUTO_INCREMENT NOT NULL,
        nomConf       Text NOT NULL,
        dateConf      Date NOT NULL,
        strategieConf Text NOT NULL,
		CONSTRAINT Configuration_PK PRIMARY KEY (idConf)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Partie
#------------------------------------------------------------

CREATE TABLE Partie(
        idP         Int NOT NULL,
        dateP       Date NOT NULL,
        nbDetective Int NOT NULL,
        victoire    Boolean,
        idConf      Int NOT NULL,
        idJ         Int NOT NULL,
		CONSTRAINT Partie_PK PRIMARY KEY (idP),
		CONSTRAINT Partie_Configuration_FK FOREIGN KEY (idConf) REFERENCES Configuration(idConf),
		CONSTRAINT Partie_Joueuses0_FK FOREIGN KEY (idJ) REFERENCES Joueuses(idJ)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Image
#------------------------------------------------------------

CREATE TABLE Image(
        idI     Int AUTO_INCREMENT NOT NULL,
        nomI    Text NOT NULL,
        cheminI Text NOT NULL,
		CONSTRAINT Image_PK PRIMARY KEY (idI)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Tour
#------------------------------------------------------------

CREATE TABLE Tour(
        nbTour Int NOT NULL,
        idP    Int NOT NULL,
		CONSTRAINT Tour_PK PRIMARY KEY (nbTour),
		CONSTRAINT Tour_Partie_FK FOREIGN KEY (idP) REFERENCES Partie(idP)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Coordonnees
#------------------------------------------------------------

CREATE TABLE Coordonnees(
        idCoord Int NOT NULL,
        coordX  Double NOT NULL,
        coordY  Double NOT NULL,
		CONSTRAINT Coordonnees_PK PRIMARY KEY (idCoord)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Routes
#------------------------------------------------------------

CREATE TABLE Routes(
        idQDepart     Int NOT NULL,
        idQArrive     Int NOT NULL,
        nbTour        Int NOT NULL,
        transport     varchar(255) NOT NULL,
		isQuartierDepart Boolean,
		CONSTRAINT Routes_PK PRIMARY KEY (idQDepart,idQArrive,nbTour),
		CONSTRAINT Routes_Quartiers0_FK FOREIGN KEY (idQDepart) REFERENCES Quartiers(idQ),
		CONSTRAINT Routes_Quartiers1_FK FOREIGN KEY (idQArrive) REFERENCES Quartiers(idQ),
		CONSTRAINT Routes_Tour0_FK FOREIGN KEY (nbTour) REFERENCES Tour(nbTour)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: IncImage
#------------------------------------------------------------

CREATE TABLE IncImage(
        idI    Int NOT NULL,
        idConf Int NOT NULL,
		CONSTRAINT Inclure_PK PRIMARY KEY (idI,idConf),
		CONSTRAINT Inclure_Image_FK FOREIGN KEY (idI) REFERENCES Image(idI),
		CONSTRAINT Inclure_Configuration0_FK FOREIGN KEY (idConf) REFERENCES Configuration(idConf)
)ENGINE=InnoDB;


#------------------------------------------------------------
# Table: Localiser
#------------------------------------------------------------

CREATE TABLE Localiser(
        idCoord Int NOT NULL,
        idQ     Int NOT NULL,
		CONSTRAINT Localiser_PK PRIMARY KEY (idCoord,idQ),
		CONSTRAINT Localiser_Coordonnees_FK FOREIGN KEY (idCoord) REFERENCES Coordonnees(idCoord),
		CONSTRAINT Localiser_Quartiers0_FK FOREIGN KEY (idQ) REFERENCES Quartiers(idQ)
)ENGINE=InnoDB;


/* Modification de la modélisation JMerise */

ALTER TABLE Routes ADD INDEX(transport);

ALTER TABLE Routes DROP FOREIGN KEY Routes_Tour0_FK;
ALTER TABLE Routes DROP FOREIGN KEY Routes_Quartiers0_FK;
ALTER TABLE Routes DROP FOREIGN KEY Routes_Quartiers1_FK;
ALTER TABLE Routes DROP PRIMARY KEY;

ALTER TABLE Routes DROP nbTour;

ALTER TABLE Routes ADD CONSTRAINT Routes_Quartiers0_FK FOREIGN KEY (idQDepart) REFERENCES Quartiers(idQ);
ALTER TABLE Routes ADD CONSTRAINT Routes_Quartiers1_FK FOREIGN KEY (idQArrive) REFERENCES Quartiers(idQ);
ALTER TABLE Routes ADD CONSTRAINT Routes_PK PRIMARY KEY (idQDepart,idQArrive,transport);


ALTER TABLE Tour DROP PRIMARY KEY;

ALTER TABLE Tour ADD idQDepart INT NOT NULL;
ALTER TABLE Tour ADD idQArrive INT NOT NULL;
ALTER TABLE Tour ADD transport varchar(255) NOT NULL;

ALTER TABLE Tour ADD CONSTRAINT Tour_Quartiers0_FK FOREIGN KEY (idQDepart) REFERENCES Routes(idQDepart);
ALTER TABLE Tour ADD CONSTRAINT Tour_Quartiers1_FK FOREIGN KEY (idQArrive) REFERENCES Routes(idQArrive);
ALTER TABLE Tour ADD CONSTRAINT Tour_Transport_FK FOREIGN KEY (transport) REFERENCES Routes(transport);
ALTER TABLE Tour ADD CONSTRAINT Tour_PK PRIMARY KEY (nbTour, idP, idQDepart, idQArrive, transport);

ALTER DATABASE p1908794 CHARACTER SET = utf8;

