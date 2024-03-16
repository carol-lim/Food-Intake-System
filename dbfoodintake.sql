-- phpMyAdmin SQL Dump
-- version 4.9.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1:3308
-- Generation Time: Jun 19, 2021 at 03:14 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.2.26

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dbfoodintake`
--

-- --------------------------------------------------------

--
-- Table structure for table `bodydetails`
--

CREATE TABLE `bodydetails` (
  `bd_id` int(10) NOT NULL,
  `user_id` int(10) NOT NULL,
  `age` int(3) NOT NULL,
  `height` double NOT NULL,
  `weight` double NOT NULL,
  `act_level` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `tdee` int(10) NOT NULL,
  `date` date NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `bodydetails`
--

INSERT INTO `bodydetails` (`bd_id`, `user_id`, `age`, `height`, `weight`, `act_level`, `tdee`, `date`) VALUES
(27, 24, 21, 160, 60, 'Lightly Active', 1834, '2021-05-22'),
(28, 24, 22, 160, 59, 'Lightly Active', 1827, '2021-05-23'),
(29, 24, 22, 161, 60, 'Lightly Active', 1836, '2021-05-24'),
(32, 24, 23, 161, 56, 'Moderately Active', 1984, '2021-05-30'),
(38, 24, 21, 161, 55, 'Moderately Active', 2000, '2021-06-11'),
(45, 31, 21, 175, 58, 'Sedentary', 1877, '2021-06-19'),
(46, 32, 21, 155, 58, 'Sedentary', 1539, '2021-06-19'),
(63, 47, 21, 154, 45, 'Lightly Active', 1570, '2021-06-19'),
(66, 49, 28, 160, 48, 'Sedentary', 1415, '2021-06-19'),
(67, 50, 22, 175, 60, 'Lightly Active', 2171, '2021-06-19'),
(68, 47, 21, 154, 45, 'Lightly Active', 1570, '2021-06-19'),
(81, 61, 21, 170, 60, 'Sedentary', 1863, '2021-06-19'),
(82, 61, 31, 170, 60, 'Sedentary', 1803, '2021-06-19'),
(83, 61, 30, 175, 64, 'Lightly Active', 2171, '2021-06-19'),
(84, 47, 22, 154, 45, 'Lightly Active', 1570, '2021-06-19');

-- --------------------------------------------------------

--
-- Table structure for table `diary`
--

CREATE TABLE `diary` (
  `diary_id` int(20) NOT NULL,
  `user_id` int(10) NOT NULL,
  `total_kcal` int(10) NOT NULL,
  `total_protein` double NOT NULL,
  `total_carbs` double NOT NULL,
  `total_fats` double NOT NULL,
  `date` date NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `diary`
--

INSERT INTO `diary` (`diary_id`, `user_id`, `total_kcal`, `total_protein`, `total_carbs`, `total_fats`, `date`) VALUES
(4, 24, 244, 19.5, 10.16, 15.475000000000001, '2021-06-13'),
(5, 24, 0, 0, 0, 0, '2021-06-18'),
(6, 24, 0, 0, 0, 0, '2021-06-19'),
(7, 31, 0, 0, 0, 0, '2021-06-19'),
(8, 32, 122, 2, 20, 4, '2021-06-19'),
(14, 61, 140, 12, 0, 10, '2021-06-19');

-- --------------------------------------------------------

--
-- Table structure for table `diaryfood`
--

CREATE TABLE `diaryfood` (
  `diary_id` int(20) NOT NULL,
  `food_id` int(10) NOT NULL,
  `portion` double NOT NULL,
  `df_kcal` double NOT NULL,
  `df_protein` double NOT NULL,
  `df_carbs` double NOT NULL,
  `df_fats` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `diaryfood`
--

INSERT INTO `diaryfood` (`diary_id`, `food_id`, `portion`, `df_kcal`, `df_protein`, `df_carbs`, `df_fats`) VALUES
(8, 173, 2, 122, 2, 20, 4),
(14, 222, 2, 140, 12, 0, 10);

-- --------------------------------------------------------

--
-- Table structure for table `food`
--

CREATE TABLE `food` (
  `food_id` int(10) NOT NULL,
  `name` varchar(100) COLLATE utf8mb4_bin NOT NULL,
  `serving_size` double NOT NULL,
  `kcal` int(10) NOT NULL,
  `protein` double NOT NULL,
  `carbs` double NOT NULL,
  `fats` double NOT NULL,
  `created_by` int(10) DEFAULT NULL,
  `created_date` date DEFAULT current_timestamp(),
  `last_updated_by` int(10) DEFAULT NULL,
  `last_updated_date` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `food`
--

INSERT INTO `food` (`food_id`, `name`, `serving_size`, `kcal`, `protein`, `carbs`, `fats`, `created_by`, `created_date`, `last_updated_by`, `last_updated_date`) VALUES
(143, 'durian', 243, 357, 4, 66, 13, 24, '2021-06-13', 24, '2021-06-13'),
(144, 'rambutan', 100, 82, 1, 20, 0, 31, '2021-06-19', NULL, NULL),
(145, 'Fresh lychee', 100, 66, 0.8, 16.5, 0.4, 31, '2021-06-19', NULL, NULL),
(146, 'dragon fruit', 100, 60, 1.2, 13, 0, 31, '2021-06-19', NULL, NULL),
(147, 'mango', 165, 99, 1.4, 24.7, 0.6, 31, '2021-06-19', NULL, NULL),
(148, 'star fruit', 91, 28, 1, 6, 0, 31, '2021-06-19', 31, '2021-06-19'),
(149, 'mandarin orange', 88, 47, 0.7, 12, 0.3, 31, '2021-06-19', NULL, NULL),
(150, 'watermelon', 100, 30, 0.6, 7.6, 0.2, 31, '2021-06-19', NULL, NULL),
(151, 'grapes', 126, 90, 0, 23, 0, 31, '2021-06-19', NULL, NULL),
(152, 'papaya', 380, 148, 2, 37, 1, 31, '2021-06-19', 31, '2021-06-19'),
(153, 'peach', 147, 60, 1, 15, 1, 31, '2021-06-19', NULL, NULL),
(154, 'pitted prunes', 11.3, 25, 0.3, 6, 0, 31, '2021-06-19', NULL, NULL),
(155, 'pear', 178, 101, 1, 27, 0, 31, '2021-06-19', NULL, NULL),
(156, 'banana', 100, 89, 1.1, 22.8, 0.3, 31, '2021-06-19', NULL, NULL),
(157, 'guava', 100, 68, 3, 14, 1, 31, '2021-06-19', NULL, NULL),
(158, 'orange', 130, 62, 1, 15, 0, 31, '2021-06-19', NULL, NULL),
(159, 'apple', 100, 52, 0.3, 13.8, 0.2, 31, '2021-06-19', NULL, NULL),
(160, 'bubble tea', 300, 271, 3.07, 58.83, 3.06, 31, '2021-06-19', NULL, NULL),
(161, 'Kfc Fried Chicken Drumstick', 60, 130, 12, 4, 8, 31, '2021-06-19', NULL, NULL),
(162, 'kuih lapis', 69, 120, 1, 22, 3, 31, '2021-06-19', NULL, NULL),
(163, 'kuih apam balik', 115, 282, 7, 51, 6, 31, '2021-06-19', NULL, NULL),
(164, 'roti jala', 55, 108, 3, 17, 3, 31, '2021-06-19', NULL, NULL),
(165, 'rojak', 315, 559, 20, 65, 25, 31, '2021-06-19', NULL, NULL),
(166, 'muar fish otak-otak', 20, 36, 2, 5, 1, 31, '2021-06-19', NULL, NULL),
(167, 'murtabak chicken', 308, 564, 42, 59, 15, 31, '2021-06-19', NULL, NULL),
(168, 'cheese cake', 122, 400, 7, 29, 29, 31, '2021-06-19', NULL, NULL),
(169, 'jobbie peanut butter', 100, 609, 33.9, 18.2, 44.5, 31, '2021-06-19', NULL, NULL),
(170, 'Gardenia 100% WholeGrain with Canadian Purple Wheat', 66, 145, 9, 21, 2, 31, '2021-06-19', NULL, NULL),
(171, 'Gardenia Fine Grain Wholemeal Bread', 60, 145, 7, 29, 1, 31, '2021-06-19', NULL, NULL),
(172, 'Massimo Wholemeal Bread', 60, 169, 5, 30, 3, 31, '2021-06-19', NULL, NULL),
(173, 'Oatly oat milk', 100, 61, 1, 10, 2, 31, '2021-06-19', NULL, NULL),
(174, 'dutch lady fresh milk', 250, 153, 8, 12, 9, 31, '2021-06-19', 31, '2021-06-19'),
(175, 'Marigold Low Fat Milk', 200, 92, 7, 11, 2, 31, '2021-06-19', NULL, NULL),
(176, 'Marigold Low-Fat Yoghurt', 140, 125, 7, 19, 3, 31, '2021-06-19', NULL, NULL),
(177, 'Fresh spring roll', 100, 70, 3, 12, 2, 31, '2021-06-19', 31, '2021-06-19'),
(178, 'Vietnamese Fresh Shrimp Spring Roll', 300, 360, 21, 48, 9, 31, '2021-06-19', NULL, NULL),
(179, 'chicken pongteh', 126, 132, 9, 3, 9, 31, '2021-06-19', NULL, NULL),
(180, 'nasi ulam', 280, 212, 6, 48, 1, 31, '2021-06-19', NULL, NULL),
(181, 'Wantan Mee Dry', 330, 411, 19, 55, 12, 31, '2021-06-19', NULL, NULL),
(182, 'Prawn dumplings', 100, 196, 14, 21, 6, 31, '2021-06-19', NULL, NULL),
(183, 'hainanese chicken rice', 162, 333, 22, 6, 24, 31, '2021-06-19', 31, '2021-06-19'),
(184, 'roti john', 200, 571, 20, 61, 27, 31, '2021-06-19', NULL, NULL),
(185, 'soup noodle', 100, 190, 5, 38, 3, 31, '2021-06-19', NULL, NULL),
(186, 'capati', 38, 107, 3, 20, 3, 31, '2021-06-19', NULL, NULL),
(187, 'thosai', 90, 196, 4, 36, 4, 31, '2021-06-19', NULL, NULL),
(188, 'kuah dal', 50, 174, 10, 24, 6, 31, '2021-06-19', 31, '2021-06-19'),
(189, 'roti canai', 100, 264, 9, 34, 10, 31, '2021-06-19', 31, '2021-06-19'),
(190, 'mee rebus', 500, 555, 21, 75, 19, 31, '2021-06-19', NULL, NULL),
(191, 'chicken porridge', 595, 211, 14, 24, 7, 31, '2021-06-19', NULL, NULL),
(192, 'fish porridge', 559, 211, 14, 32, 3, 31, '2021-06-19', NULL, NULL),
(193, 'laksa', 660, 432, 21, 83, 2, 31, '2021-06-19', NULL, NULL),
(194, 'nasi kerabu', 300, 535, 24, 50, 9, 31, '2021-06-19', NULL, NULL),
(195, 'daging rendang', 100, 171, 20, 8, 7, 31, '2021-06-19', NULL, NULL),
(196, 'Ayam Masak Merah', 60, 82, 8, 2, 5, 31, '2021-06-19', NULL, NULL),
(197, 'pumpkin raw', 100, 26, 1, 8, 0, 31, '2021-06-19', NULL, NULL),
(198, 'potato raw', 100, 77, 2, 17, 0, 31, '2021-06-19', NULL, NULL),
(199, 'Steamed Yam', 100, 116, 2, 28, 0, 31, '2021-06-19', NULL, NULL),
(200, 'carrots', 78, 27, 1, 6, 0, 31, '2021-06-19', NULL, NULL),
(201, 'salmon raw', 100, 208, 20, 0, 13, 31, '2021-06-19', NULL, NULL),
(202, 'Portobello Mushroom raw', 100, 22, 3, 3, 0, 31, '2021-06-19', 31, '2021-06-19'),
(203, 'sweet potato leaves', 100, 42, 3, 9, 1, 31, '2021-06-19', NULL, NULL),
(204, 'napa cabbage', 85, 10, 1, 2, 0, 31, '2021-06-19', NULL, NULL),
(205, 'Snake Beans, Raw', 100, 14, 3, 8, 0, 31, '2021-06-19', NULL, NULL),
(206, 'bok choy raw', 100, 13, 2, 2, 0, 31, '2021-06-19', NULL, NULL),
(207, 'bean sprouts', 100, 52, 5, 6, 1, 31, '2021-06-19', NULL, NULL),
(208, 'ladies finger', 100, 44, 2, 9, 0, 31, '2021-06-19', NULL, NULL),
(209, 'winged bean ', 100, 148, 12, 28, 1, 31, '2021-06-19', NULL, NULL),
(210, 'kangkung raw', 100, 29, 3, 5, 0, 31, '2021-06-19', NULL, NULL),
(211, 'broccoli raw', 100, 34, 3, 7, 0, 31, '2021-06-19', NULL, NULL),
(212, 'choy sum raw', 85, 20, 2, 3, 0, 31, '2021-06-19', NULL, NULL),
(213, 'eggplant raw', 100, 25, 1, 6, 0, 31, '2021-06-19', NULL, NULL),
(214, 'cucumber', 30, 4, 0, 1, 0, 31, '2021-06-19', NULL, NULL),
(215, 'yardlong bean', 100, 47, 3, 8, 0, 31, '2021-06-19', NULL, NULL),
(216, 'lamb', 100, 250, 21, 0, 18, 31, '2021-06-19', NULL, NULL),
(217, 'duck, cooked', 140, 472, 27, 0, 40, 31, '2021-06-19', NULL, NULL),
(218, 'pork raw', 200, 305, 19, 18, 17, 31, '2021-06-19', NULL, NULL),
(219, 'raw beef', 75, 250, 26, 0, 15, 31, '2021-06-19', NULL, NULL),
(220, 'raw chicken breast', 100, 110, 31, 0, 1, 31, '2021-06-19', 31, '2021-06-19'),
(221, 'fish cooked', 188, 164, 35, 0, 0, 31, '2021-06-19', NULL, NULL),
(222, 'egg', 50, 70, 6, 0, 5, 31, '2021-06-19', NULL, NULL),
(223, 'Hong Kong Style Egg Tart', 85, 203, 4, 22, 10, 31, '2021-06-19', NULL, NULL),
(224, 'curry puff', 71, 246, 5, 20, 16, 31, '2021-06-19', NULL, NULL),
(225, 'McD White Coffee', 300, 25, 2, 2, 1, 31, '2021-06-19', NULL, NULL),
(226, 'teh Tarik', 250, 83, 4, 23, 3, 31, '2021-06-19', NULL, NULL),
(227, 'milo', 33, 121, 3, 21, 3, 31, '2021-06-19', NULL, NULL),
(228, 'Chee Cheong Fun', 100, 131, 5, 16, 9, 31, '2021-06-19', NULL, NULL),
(229, 'soya', 30, 130, 13, 11, 4, 31, '2021-06-19', NULL, NULL),
(230, 'sweet potato', 100, 86, 2, 20, 0, 31, '2021-06-19', NULL, NULL),
(231, 'nasi lemak', 275, 530, 22, 48, 28, 31, '2021-06-19', NULL, NULL),
(232, 'mee goreng mamak', 200, 331, 11, 48, 11, 31, '2021-06-19', NULL, NULL),
(235, 'quaker instant oatmeal', 35, 133, 4, 20, 3, 61, '2021-06-19', 61, '2021-06-19');

-- --------------------------------------------------------

--
-- Table structure for table `goal`
--

CREATE TABLE `goal` (
  `goal_id` int(10) NOT NULL,
  `user_id` int(10) NOT NULL,
  `fitness_goal` varchar(30) COLLATE utf8mb4_bin NOT NULL,
  `kcal_goal` int(10) NOT NULL,
  `protein_perc` int(10) NOT NULL,
  `carbs_perc` int(10) NOT NULL,
  `fats_perc` int(10) NOT NULL,
  `protein_gram` int(10) NOT NULL,
  `carbs_gram` int(10) NOT NULL,
  `fats_gram` int(10) NOT NULL,
  `date` date NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `goal`
--

INSERT INTO `goal` (`goal_id`, `user_id`, `fitness_goal`, `kcal_goal`, `protein_perc`, `carbs_perc`, `fats_perc`, `protein_gram`, `carbs_gram`, `fats_gram`, `date`) VALUES
(44, 24, 'Cut', 1500, 30, 35, 35, 112, 131, 58, '2021-06-18'),
(48, 31, 'Cut', 1407, 20, 50, 30, 70, 175, 46, '2021-06-19'),
(49, 32, 'Cut', 1154, 20, 50, 30, 57, 144, 38, '2021-06-19'),
(66, 47, 'Gain', 1727, 20, 50, 30, 86, 215, 57, '2021-06-19'),
(69, 49, 'Gain', 1556, 20, 50, 30, 77, 194, 51, '2021-06-19'),
(70, 50, 'Cut', 1628, 20, 50, 30, 81, 203, 54, '2021-06-19'),
(71, 47, 'Gain', 1727, 20, 50, 30, 86, 215, 57, '2021-06-19'),
(84, 61, 'Cut', 1397, 20, 50, 30, 69, 174, 46, '2021-06-19'),
(85, 61, 'Cut', 1352, 20, 50, 30, 67, 169, 45, '2021-06-19'),
(86, 61, 'Cut', 1628, 20, 50, 30, 81, 203, 54, '2021-06-19'),
(87, 61, 'Gain', 1700, 30, 40, 30, 127, 170, 56, '2021-06-19'),
(88, 47, 'Gain', 1727, 20, 50, 30, 86, 215, 57, '2021-06-19');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `user_id` int(10) NOT NULL,
  `name` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `gender` char(1) COLLATE utf8mb4_bin NOT NULL,
  `yob` int(4) NOT NULL,
  `password` varchar(50) COLLATE utf8mb4_bin NOT NULL,
  `email` varchar(50) COLLATE utf8mb4_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`user_id`, `name`, `gender`, `yob`, `password`, `email`) VALUES
(24, 'Nur Siti', 'F', 2000, 'Nursiti123-', 'nursiti@gmail.com'),
(31, 'Fahan', 'M', 2000, 'Fahan3366-', 'fahan@gmail.com'),
(32, 'Carol', 'F', 2000, 'Carol0412-', 'carol@gmail.com'),
(47, 'Yirin', 'F', 1999, 'Yirin123*', 'yirin@gmail.com'),
(49, 'Fatimah', 'F', 1993, 'Fatimah123*', 'fatimah@gmail.com'),
(50, 'Kalil', 'M', 1999, 'Kalil123*', 'kalil@gmail.com'),
(61, 'Fahan', 'M', 2000, 'Farhan12345*', 'farhan@gmail.com');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `bodydetails`
--
ALTER TABLE `bodydetails`
  ADD PRIMARY KEY (`bd_id`),
  ADD KEY `FK_BodyDetailsUser` (`user_id`);

--
-- Indexes for table `diary`
--
ALTER TABLE `diary`
  ADD PRIMARY KEY (`diary_id`),
  ADD KEY `FK_DiaryUser` (`user_id`);

--
-- Indexes for table `diaryfood`
--
ALTER TABLE `diaryfood`
  ADD KEY `FK_BridgeDiary` (`diary_id`),
  ADD KEY `FK_BridgeFood` (`food_id`);

--
-- Indexes for table `food`
--
ALTER TABLE `food`
  ADD PRIMARY KEY (`food_id`),
  ADD KEY `FK_FoodCreator` (`created_by`),
  ADD KEY `FK_FoodUpdator` (`last_updated_by`);

--
-- Indexes for table `goal`
--
ALTER TABLE `goal`
  ADD PRIMARY KEY (`goal_id`),
  ADD KEY `FK_GoalUser` (`user_id`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `bodydetails`
--
ALTER TABLE `bodydetails`
  MODIFY `bd_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=85;

--
-- AUTO_INCREMENT for table `diary`
--
ALTER TABLE `diary`
  MODIFY `diary_id` int(20) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `food`
--
ALTER TABLE `food`
  MODIFY `food_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=236;

--
-- AUTO_INCREMENT for table `goal`
--
ALTER TABLE `goal`
  MODIFY `goal_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=89;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `user_id` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=62;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `bodydetails`
--
ALTER TABLE `bodydetails`
  ADD CONSTRAINT `FK_BodyDetailsUser` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `diary`
--
ALTER TABLE `diary`
  ADD CONSTRAINT `FK_DiaryUser` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `diaryfood`
--
ALTER TABLE `diaryfood`
  ADD CONSTRAINT `FK_BridgeDiary` FOREIGN KEY (`diary_id`) REFERENCES `diary` (`diary_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_BridgeFood` FOREIGN KEY (`food_id`) REFERENCES `food` (`food_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `food`
--
ALTER TABLE `food`
  ADD CONSTRAINT `FK_FoodCreator` FOREIGN KEY (`created_by`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `FK_FoodUpdator` FOREIGN KEY (`last_updated_by`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `goal`
--
ALTER TABLE `goal`
  ADD CONSTRAINT `FK_GoalUser` FOREIGN KEY (`user_id`) REFERENCES `user` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
