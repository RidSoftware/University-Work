-- phpMyAdmin SQL Dump
-- version 3.5.2
-- http://www.phpmyadmin.net
--
-- Host: mysql-server-1.macs.hw.ac.uk
-- Generation Time: Jan 18, 2013 at 03:34 PM
-- Server version: 5.0.95
-- PHP Version: 5.3.3

SET FOREIGN_KEY_CHECKS=0;
SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;



-- --------------------------------------------------------

--
-- Table structure for table 'DBDeadline'
--

DROP TABLE IF EXISTS DBDeadline;
CREATE TABLE IF NOT EXISTS DBDeadline (
  projPNum int(11) NOT NULL,
  dLineDate date NOT NULL,
  dLineType enum('Bid','Intermediate','Final') NOT NULL default 'Bid',
  PRIMARY KEY  (projPNum,dLineDate)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'DBDeadline'
--

INSERT INTO DBDeadline VALUES(3, '2013-01-25', 'Bid');
INSERT INTO DBDeadline VALUES(3, '2013-04-26', 'Intermediate');
INSERT INTO DBDeadline VALUES(4, '2013-01-25', 'Intermediate');
INSERT INTO DBDeadline VALUES(4, '2013-02-21', 'Final');
INSERT INTO DBDeadline VALUES(5, '2013-02-21', 'Final');

-- --------------------------------------------------------

--
-- Table structure for table 'DBDepartment'
--

DROP TABLE IF EXISTS DBDepartment;
CREATE TABLE IF NOT EXISTS DBDepartment (
  dNum int(11) NOT NULL,
  dName varchar(15) NOT NULL,
  mgrSsn int(11) default NULL,
  mgrStartDate date default NULL,
  PRIMARY KEY  (dNum),
  UNIQUE KEY dName (dName),
  KEY mgrSsn (mgrSsn)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'DBDepartment'
--

INSERT INTO DBDepartment VALUES(1, 'HR', 301, '2012-02-05');
INSERT INTO DBDepartment VALUES(2, 'Computing', 217, '1999-02-22');
INSERT INTO DBDepartment VALUES(3, 'Physics', 222, '2002-03-02');
INSERT INTO DBDepartment VALUES(4, 'Maths', 225, '2010-03-12');
INSERT INTO DBDepartment VALUES(5, 'Chemistry', 233, '2009-04-02');
INSERT INTO DBDepartment VALUES(6, 'Payroll', 279, '2012-02-09');
INSERT INTO DBDepartment VALUES(7, 'Stats', NULL, NULL);
INSERT INTO DBDepartment VALUES(8, 'Building', NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table 'DBEmployee'
--

DROP TABLE IF EXISTS DBEmployee;
CREATE TABLE IF NOT EXISTS DBEmployee (
  ssn int(11) NOT NULL,
  firstnames varchar(12) NOT NULL,
  lastname varchar(12) NOT NULL,
  dateOfBirth date default NULL,
  gender enum('M','F') NOT NULL,
  salary int(11) NOT NULL,
  empdNum int(11) default NULL,
  supssn int(11) default NULL,
  PRIMARY KEY  (ssn),
  KEY empdNum (empdNum),
  KEY supssn (supssn)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'DBEmployee'
--

INSERT INTO DBEmployee VALUES(122, 'Keith', 'Brown', '1953-03-25', 'M', 30000, 1, 123);
INSERT INTO DBEmployee VALUES(123, 'Gordon', 'Smith', '1953-02-12', 'M', 25000, 1, 124);
INSERT INTO DBEmployee VALUES(124, 'Keith', 'Johnson', '1974-07-01', 'M', 28000, 2, NULL);
INSERT INTO DBEmployee VALUES(125, 'Jane', 'Jones', '1980-10-20', 'F', 14000, 2, 124);
INSERT INTO DBEmployee VALUES(126, 'Mary', 'Smith', '2000-01-09', 'F', 30500, NULL, NULL);
INSERT INTO DBEmployee VALUES(212, 'Audrey', 'Glancy', '1981-11-23', 'F', 37000, 1, 221);
INSERT INTO DBEmployee VALUES(213, 'Chong', 'Gray', '1974-12-22', 'M', 23000, 1, 212);
INSERT INTO DBEmployee VALUES(214, 'Yi', 'Hacking', '1956-10-06', 'M', 33000, 1, 212);
INSERT INTO DBEmployee VALUES(215, 'Christopher', 'Halcrow', '1990-02-04', 'M', 18000, 1, 212);
INSERT INTO DBEmployee VALUES(216, 'William', 'Harrison', '1965-06-23', 'M', 23000, 1, 212);
INSERT INTO DBEmployee VALUES(217, 'Neil', 'Hawley', '1966-05-12', 'M', 23000, 2, 221);
INSERT INTO DBEmployee VALUES(218, 'Douglas', 'Herd', '1978-04-05', 'M', 18000, 2, 221);
INSERT INTO DBEmployee VALUES(219, 'Rosemary', 'Hodge', '1987-04-27', 'F', 33000, 2, 217);
INSERT INTO DBEmployee VALUES(220, 'David', 'Housard', '1990-05-17', 'M', 29000, 2, 217);
INSERT INTO DBEmployee VALUES(221, 'Catriona', 'Howell', '1960-12-24', 'F', 40000, 2, NULL);
INSERT INTO DBEmployee VALUES(222, 'Fraser', 'Ioannides', '1967-06-08', 'M', 23000, NULL, 221);
INSERT INTO DBEmployee VALUES(223, 'Sanjay', 'James', '1991-05-09', 'M', 18000, NULL, 222);
INSERT INTO DBEmployee VALUES(224, 'Aurangzeb', 'Jones', '1955-12-20', 'M', 29000, NULL, 222);
INSERT INTO DBEmployee VALUES(225, 'Jeremiah', 'Kaur', '1959-07-02', 'M', 29000, 4, 221);
INSERT INTO DBEmployee VALUES(226, 'Edward', 'Kemp', '1982-11-21', 'M', 23000, 4, NULL);
INSERT INTO DBEmployee VALUES(227, 'Stephan', 'Khoo', '1974-12-16', 'M', 33000, 4, NULL);
INSERT INTO DBEmployee VALUES(228, 'Robert', 'King', '1962-11-06', 'M', 29000, 4, 221);
INSERT INTO DBEmployee VALUES(233, 'David', 'Lee', '1982-10-16', 'M', 18000, 5, 221);
INSERT INTO DBEmployee VALUES(234, 'Cher', 'Liau', '1977-02-06', 'F', 23000, 5, 233);
INSERT INTO DBEmployee VALUES(235, 'Barbara', 'Mackenzie', '1954-06-16', 'F', 18000, 5, 233);
INSERT INTO DBEmployee VALUES(236, 'Judith', 'Mackintosh', '1977-10-26', 'F', 29000, 5, 233);
INSERT INTO DBEmployee VALUES(237, 'James', 'Macleod', '1979-12-06', 'M', 18000, 5, 233);
INSERT INTO DBEmployee VALUES(279, 'Heather', 'Tempest', '1965-11-23', 'F', 23000, 6, 221);
INSERT INTO DBEmployee VALUES(280, 'Anne', 'Thompson', '1966-12-09', 'F', 29000, 6, 279);
INSERT INTO DBEmployee VALUES(281, 'Arvind', 'Thomson', '1990-02-27', 'M', 18000, 6, 279);
INSERT INTO DBEmployee VALUES(282, 'Joan', 'Tognarelli', '1963-11-09', 'F', 29000, 6, 279);
INSERT INTO DBEmployee VALUES(283, 'Kristy', 'Usher', '1961-11-06', 'F', 19000, 6, 279);
INSERT INTO DBEmployee VALUES(284, 'Kyriakos', 'Waweru', '1980-02-08', 'M', 29000, 6, 279);
INSERT INTO DBEmployee VALUES(285, 'Dimitrios', 'Wilson', NULL, 'M', 35000, 6, 279);
INSERT INTO DBEmployee VALUES(286, 'William', 'Wong', '1960-04-02', 'M', 33000, 6, 279);
INSERT INTO DBEmployee VALUES(287, 'Denis', 'Yates', '1950-03-01', 'M', 27000, 6, 279);
INSERT INTO DBEmployee VALUES(300, 'Jane', 'Barr', '1991-11-13', 'F', 22000, 2, 220);
INSERT INTO DBEmployee VALUES(301, 'Susan', 'Gibson', '1980-12-03', 'F', 15000, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table 'DBLocation'
--

DROP TABLE IF EXISTS DBLocation;
CREATE TABLE IF NOT EXISTS DBLocation (
  ldNum int(11) NOT NULL,
  loc varchar(20) NOT NULL default 'Riccarton',
  PRIMARY KEY  (ldNum,loc)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'DBLocation'
--

INSERT INTO DBLocation VALUES(1, 'Hillend');
INSERT INTO DBLocation VALUES(1, 'Riccarton');
INSERT INTO DBLocation VALUES(2, 'Riccarton');
INSERT INTO DBLocation VALUES(4, 'Hillend');
INSERT INTO DBLocation VALUES(4, 'Mossfoot');
INSERT INTO DBLocation VALUES(4, 'Riccarton');
INSERT INTO DBLocation VALUES(5, 'Riccarton');

-- --------------------------------------------------------

--
-- Table structure for table 'DBProject'
--

DROP TABLE IF EXISTS DBProject;
CREATE TABLE IF NOT EXISTS DBProject (
  pNum int(2) NOT NULL auto_increment,
  pName varchar(20) NOT NULL,
  pdNum int(11) NOT NULL,
  PRIMARY KEY  (pNum),
  UNIQUE KEY pName (pName),
  KEY pdNum (pdNum)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=13 ;

--
-- Dumping data for table 'DBProject'
--

INSERT INTO DBProject VALUES(1, 'Turing', 5);
INSERT INTO DBProject VALUES(2, 'Faraday', 5);
INSERT INTO DBProject VALUES(3, 'Jupiter', 5);
INSERT INTO DBProject VALUES(4, 'Mars', 3);
INSERT INTO DBProject VALUES(5, 'Uranus', 3);
INSERT INTO DBProject VALUES(6, 'Venus', 3);
INSERT INTO DBProject VALUES(7, 'Platinum', 4);
INSERT INTO DBProject VALUES(8, 'Galaxy', 2);
INSERT INTO DBProject VALUES(9, 'Mozart', 6);
INSERT INTO DBProject VALUES(10, 'Chopin', 6);
INSERT INTO DBProject VALUES(11, 'Newton', 7);
INSERT INTO DBProject VALUES(12, 'Halliday', 7);

-- --------------------------------------------------------

--
-- Table structure for table 'DBWorksOn'
--

DROP TABLE IF EXISTS DBWorksOn;
CREATE TABLE IF NOT EXISTS DBWorksOn (
  wssn int(11) NOT NULL,
  wpNum int(2) NOT NULL,
  hours int(11) default NULL,
  PRIMARY KEY  (wssn,wpNum),
  KEY wpNum (wpNum)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table 'DBWorksOn'
--

INSERT INTO DBWorksOn VALUES(122, 4, 10);
INSERT INTO DBWorksOn VALUES(123, 3, 5);
INSERT INTO DBWorksOn VALUES(123, 4, 20);
INSERT INTO DBWorksOn VALUES(212, 1, 50);
INSERT INTO DBWorksOn VALUES(212, 2, 50);
INSERT INTO DBWorksOn VALUES(212, 4, 5);
INSERT INTO DBWorksOn VALUES(213, 1, 50);
INSERT INTO DBWorksOn VALUES(213, 2, 50);
INSERT INTO DBWorksOn VALUES(213, 3, 50);
INSERT INTO DBWorksOn VALUES(213, 6, 50);
INSERT INTO DBWorksOn VALUES(213, 7, 2);
INSERT INTO DBWorksOn VALUES(214, 2, 50);
INSERT INTO DBWorksOn VALUES(215, 11, 50);
INSERT INTO DBWorksOn VALUES(215, 12, 50);
INSERT INTO DBWorksOn VALUES(216, 6, 50);
INSERT INTO DBWorksOn VALUES(217, 7, 50);
INSERT INTO DBWorksOn VALUES(218, 6, 50);
INSERT INTO DBWorksOn VALUES(219, 1, 50);
INSERT INTO DBWorksOn VALUES(220, 2, 50);
INSERT INTO DBWorksOn VALUES(222, 3, 50);
INSERT INTO DBWorksOn VALUES(223, 3, 45);
INSERT INTO DBWorksOn VALUES(224, 3, 50);
INSERT INTO DBWorksOn VALUES(225, 4, 50);
INSERT INTO DBWorksOn VALUES(226, 4, 50);
INSERT INTO DBWorksOn VALUES(227, 4, 50);
INSERT INTO DBWorksOn VALUES(233, 5, 50);
INSERT INTO DBWorksOn VALUES(234, 5, 50);
INSERT INTO DBWorksOn VALUES(235, 5, 50);
INSERT INTO DBWorksOn VALUES(236, 5, 50);
INSERT INTO DBWorksOn VALUES(237, 4, 50);
INSERT INTO DBWorksOn VALUES(285, 6, 50);
INSERT INTO DBWorksOn VALUES(286, 6, 50);
INSERT INTO DBWorksOn VALUES(287, 6, 50);
INSERT INTO DBWorksOn VALUES(300, 11, 50);
INSERT INTO DBWorksOn VALUES(300, 12, 50);
INSERT INTO DBWorksOn VALUES(301, 11, 50);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `DBDeadline`
--
ALTER TABLE `DBDeadline`
  ADD CONSTRAINT DBDeadline_ibfk_3 FOREIGN KEY (projPNum) REFERENCES DBProject (pNum);

--
-- Constraints for table `DBDepartment`
--
ALTER TABLE `DBDepartment`
  ADD CONSTRAINT DBDepartment_ibfk_3 FOREIGN KEY (mgrSsn) REFERENCES DBEmployee (ssn) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Constraints for table `DBEmployee`
--
ALTER TABLE `DBEmployee`
  ADD CONSTRAINT DBEmployee_ibfk_5 FOREIGN KEY (supssn) REFERENCES DBEmployee (ssn) ON DELETE SET NULL ON UPDATE CASCADE,
  ADD CONSTRAINT DBEmployee_ibfk_6 FOREIGN KEY (empdNum) REFERENCES DBDepartment (dNum) ON DELETE SET NULL ON UPDATE CASCADE;

--
-- Constraints for table `DBLocation`
--
ALTER TABLE `DBLocation`
  ADD CONSTRAINT DBLocation_ibfk_2 FOREIGN KEY (ldNum) REFERENCES DBDepartment (dNum) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `DBProject`
--
ALTER TABLE `DBProject`
  ADD CONSTRAINT DBProject_ibfk_1 FOREIGN KEY (pdNum) REFERENCES DBDepartment (dNum) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `DBWorksOn`
--
ALTER TABLE `DBWorksOn`
  ADD CONSTRAINT DBWorksOn_ibfk_3 FOREIGN KEY (wssn) REFERENCES DBEmployee (ssn) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT DBWorksOn_ibfk_4 FOREIGN KEY (wpNum) REFERENCES DBProject (pNum) ON DELETE CASCADE ON UPDATE CASCADE;
SET FOREIGN_KEY_CHECKS=1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
