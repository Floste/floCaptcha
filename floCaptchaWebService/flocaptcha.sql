-- phpMyAdmin SQL Dump
-- version 3.2.5
-- http://www.phpmyadmin.net
--
-- Serveur: 127.0.0.1
-- Généré le : Dim 24 Octobre 2010 à 16:28
-- Version du serveur: 5.1.43
-- Version de PHP: 5.3.2

SET FOREIGN_KEY_CHECKS=0;
SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données: `flocaptcha`
--

-- --------------------------------------------------------

--
-- Structure de la table `captcha`
--

CREATE TABLE IF NOT EXISTS `captcha` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `idCaptcha` varchar(23) COLLATE utf8_bin NOT NULL,
  `texte` varchar(10) COLLATE utf8_bin NOT NULL,
  `date_creation` datetime NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `idCaptcha` (`idCaptcha`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=114 ;
SET FOREIGN_KEY_CHECKS=1;
