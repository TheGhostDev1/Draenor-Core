-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               5.5.9-log - MySQL Community Server (GPL)
-- Server OS:                    Win32
-- HeidiSQL Version:             10.3.0.5771
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Dumping structure for table world.areatrigger_move_splines
CREATE TABLE IF NOT EXISTS `areatrigger_move_splines` (
  `move_curve_id` int(11) NOT NULL,
  `path_id` int(11) NOT NULL DEFAULT '0',
  `path_x` float DEFAULT NULL,
  `path_y` float DEFAULT NULL,
  `path_z` float DEFAULT NULL,
  PRIMARY KEY (`move_curve_id`,`path_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Dumping data for table world.areatrigger_move_splines: ~306 rows (approximately)
DELETE FROM `areatrigger_move_splines`;
/*!40000 ALTER TABLE `areatrigger_move_splines` DISABLE KEYS */;
INSERT INTO `areatrigger_move_splines` (`move_curve_id`, `path_id`, `path_x`, `path_y`, `path_z`) VALUES
	(0, 0, 0, 0, 0),
	(0, 1, 0, 0, 0),
	(0, 2, 0, -1.74392, 0),
	(0, 3, 0, -1.74392, 0),
	(0, 4, 0.669568, -14.7977, 0),
	(0, 5, 0.654675, -13.2985, 0),
	(0, 6, 0.593885, -11.7992, 0),
	(0, 7, 0.487805, -10.2999, 0),
	(0, 8, 0.48219, -8.80066, 0),
	(0, 9, 0.412122, -7.30139, 0),
	(0, 10, 0.340344, -5.80212, 0),
	(0, 11, 0.499524, -4.30286, 0),
	(0, 12, 0.326428, -2.80359, 0),
	(0, 13, 0.146497, -1.30432, 0),
	(0, 14, -0.0156126, 0.194946, 0),
	(0, 15, -0.0693235, 1.69421, 0),
	(0, 16, -0.511706, 3.19348, 0),
	(0, 17, -0.697253, 4.69275, 0),
	(0, 18, -0.697253, 4.69275, 0),
	(0, 19, -0.772077, 1.52441, 0),
	(0, 20, -0.88991, 1.63232, 0),
	(0, 21, -1.02736, 1.73975, 0),
	(0, 22, -1.02736, 1.73975, 0),
	(463, 0, 0, 0, 0),
	(463, 1, 0, 0, 0),
	(463, 2, 0, 14.443, 0),
	(463, 3, 0, 14.443, 0),
	(470, 0, 0.0000038147, 0.0773926, 0),
	(470, 1, 0.0000038147, 0.0773926, 0),
	(470, 2, 0.0000038147, -0.0454102, 0),
	(470, 3, 0.0000038147, -0.392334, 0),
	(470, 4, 0.0000038147, -0.901856, 0),
	(470, 5, 0.0000038147, -1.48022, 0),
	(470, 6, 0.0000038147, -2.01465, 0),
	(470, 7, 0.0000038147, -2.38745, 0),
	(470, 8, 0.0000038147, -2.46875, 0),
	(470, 9, 0.0000038147, -2.21411, 0),
	(470, 10, 0.0000038147, -1.57959, 0),
	(470, 11, 0.0000038147, -0.57959, 0),
	(470, 12, 0.0000038147, 0.720459, 0),
	(470, 13, 0.0000038147, 2.20727, 0),
	(470, 14, 0.0000038147, 3.73096, 0),
	(470, 15, 0.0000038147, 5.11743, 0),
	(470, 16, 0.0000038147, 6.21582, 0),
	(470, 17, 0.0000038147, 6.78101, 0),
	(470, 18, 0.0000038147, 6.74316, 0),
	(470, 19, 0.0000038147, 6.03467, 0),
	(470, 20, 0.0000038147, 4.65454, 0),
	(470, 21, 0.0000038147, 2.6731, 0),
	(470, 22, 0.0000038147, 0.0773926, 0),
	(470, 23, 0.0000038147, -2.62402, 0),
	(470, 24, 0.0000038147, -2.62402, 0),
	(514, 0, 0, 0, 0),
	(514, 1, 0, 0, 0),
	(514, 2, 0, 1.02222, 0),
	(514, 3, 0, 2.00952, 0),
	(514, 4, 0, 2.96216, 0),
	(514, 5, 0, 3.88, 0),
	(514, 6, 0, 4.76306, 0),
	(514, 7, 0, 5.61133, 0),
	(514, 8, 0, -9.84338, 0),
	(514, 9, 0, -20.7776, 0),
	(514, 10, 0, -25.2447, 0),
	(514, 11, 0, -23.2447, 0),
	(514, 12, 0, -22.4767, 0),
	(514, 13, 0, -20.3657, 0),
	(514, 14, 0, -17.6681, 0),
	(514, 15, 0, -13.8373, 0),
	(514, 16, 0, -3.44238, 0),
	(514, 17, 0, 1.31262, 0),
	(514, 18, 0, 2.49512, 0),
	(514, 19, 0, 0.10498, 0),
	(514, 20, 0, 0, 0),
	(514, 21, 0, 0, 0),
	(515, 0, 0, 0, 0),
	(515, 1, 0, 0, 0),
	(515, 2, -0.192, 4.997, 0),
	(515, 3, -0.42, 9.992, 0),
	(515, 4, -0.683, 14.985, 0),
	(515, 5, -0.982, 19.978, 0),
	(515, 6, -1.316, 24.969, 0),
	(515, 7, -1.686, 29.96, 0),
	(515, 8, -16.24, 24.448, 0),
	(515, 9, -26.175, 19.098, 0),
	(515, 10, -29.502, 13.979, 0),
	(515, 11, -27.212, 9.056, 0),
	(515, 12, -24.201, 4.158, 0),
	(515, 13, -20.808, -0.726, 0),
	(515, 14, -16.815, -5.59, 0),
	(515, 15, -11.664, 10.413, 0),
	(515, 16, 0.193, -15.002, 0),
	(515, 17, 3.815, -9.873, 0),
	(515, 18, 3.786, -4.871, 0),
	(515, 19, 0.108, 0.004, 0),
	(515, 20, 0, 0, 0),
	(515, 21, 0, 0, 0),
	(516, 0, 0, 0, 0),
	(516, 1, 0, 0, 0),
	(516, 2, 0, -4.78674, 0),
	(516, 3, 0, -9.58386, 0),
	(516, 4, 0, -14.3914, 0),
	(516, 5, 0, -19.2092, 0),
	(516, 6, 0, -24.0376, 0),
	(516, 7, 0, -28.8762, 0),
	(516, 8, 0, -28.4034, 0),
	(516, 9, 0, -26.5795, 0),
	(516, 10, 0, -22.8225, 0),
	(516, 11, 0, -17.1325, 0),
	(516, 12, 0, -11.8107, 0),
	(516, 13, 0, -6.0874, 0),
	(516, 14, 0, -0.188843, 0),
	(516, 15, 0, 6.04846, 0),
	(516, 16, 0, 14.2478, 0),
	(516, 17, 0, 10.5769, 0),
	(516, 18, 0, 5.83801, 0),
	(516, 19, 0, 0.0313721, 0),
	(516, 20, 0, 0, 0),
	(516, 21, 0, 0, 0),
	(517, 0, 0, 0, 0),
	(517, 1, 0, 0, 0),
	(517, 2, 0, 3.42297, 0),
	(517, 3, 0, 6.87195, 0),
	(517, 4, 0, 10.347, 0),
	(517, 5, 0, 13.848, 0),
	(517, 6, 0, 17.375, 0),
	(517, 7, 0, 20.928, 0),
	(517, 8, 0, 28.2961, 0),
	(517, 9, 0, 32.2843, 0),
	(517, 10, 0, 31.437, 0),
	(517, 11, 0, 26.4783, 0),
	(517, 12, 0, 20.9929, 0),
	(517, 13, 0, 15.2273, 0),
	(517, 14, 0, 9.02307, 0),
	(517, 15, 0, 1.97144, 0),
	(517, 16, 0, -9.98792, 0),
	(517, 17, 0, -9.35596, 0),
	(517, 18, 0, -6.05286, 0),
	(517, 19, 0, -0.0784912, 0),
	(517, 20, 0, 0, 0),
	(517, 21, 0, 0, 0),
	(518, 0, 0, 0, 0),
	(518, 1, 0, 0, 0),
	(518, 2, 0, -1.44482, 0),
	(518, 3, 0, -2.85571, 0),
	(518, 4, 0, -4.23254, 0),
	(518, 5, 0, -5.57544, 0),
	(518, 6, 0, -6.88428, 0),
	(518, 7, 0, -8.15906, 0),
	(518, 8, 0, 7.396, 0),
	(518, 9, 0, 18.5315, 0),
	(518, 10, 0, 23.3444, 0),
	(518, 11, 0, 21.8346, 0),
	(518, 12, 0, 21.5293, 0),
	(518, 13, 0, 19.9109, 0),
	(518, 14, 0, 17.719, 0),
	(518, 15, 0, 14.4193, 0),
	(518, 16, 0, 4.70203, 0),
	(518, 17, 0, -0.392212, 0),
	(518, 18, 0, -1.99377, 0),
	(518, 19, 0, -0.102661, 0),
	(518, 20, 0, 0, 0),
	(518, 21, 0, 0, 0),
	(519, 0, 0, 0, 0),
	(519, 1, 0, 0, 0),
	(519, 2, 0, 3.70386, 0),
	(519, 3, 0, 7.38391, 0),
	(519, 4, 0, 11.0402, 0),
	(519, 5, 0, 14.6726, 0),
	(519, 6, 0, 18.2812, 0),
	(519, 7, 0, 21.8661, 0),
	(519, 8, 0, 8.28931, 0),
	(519, 9, 0, -2.19519, 0),
	(519, 10, 0, -8.25562, 0),
	(519, 11, 0, -10.5543, 0),
	(519, 12, 0, -12.3712, 0),
	(519, 13, 0, -13.9318, 0),
	(519, 14, 0, -15.0909, 0),
	(519, 15, 0, -15.475, 0),
	(519, 16, 0, -11.3685, 0),
	(519, 17, 0, -5.11121, 0),
	(519, 18, 0, -1.29773, 0),
	(519, 19, 0, 0.0718994, 0),
	(519, 20, 0, 0, 0),
	(519, 21, 0, 0, 0),
	(520, 0, 0, 0, 0),
	(520, 1, 0, 0, 0),
	(520, 2, 0, -4.3645, 0),
	(520, 3, 0, -8.71167, 0),
	(520, 4, 0, -13.0417, 0),
	(520, 5, 0, -17.3545, 0),
	(520, 6, 0, -21.65, 0),
	(520, 7, 0, -25.9283, 0),
	(520, 8, 0, -14.4105, 0),
	(520, 9, 0, -5.13318, 0),
	(520, 10, 0, 0.938721, 0),
	(520, 11, 0, 3.8053, 0),
	(520, 12, 0, 7.28247, 0),
	(520, 13, 0, 10.0941, 0),
	(520, 14, 0, 12.6149, 0),
	(520, 15, 0, 14.574, 0),
	(520, 16, 0, 13.2797, 0),
	(520, 17, 0, 7.06506, 0),
	(520, 18, 0, 2.62122, 0),
	(520, 19, 0, -0.0520019, 0),
	(520, 20, 0, 0, 0),
	(520, 21, 0, 0, 0),
	(521, 0, 0, 0, 0),
	(521, 1, 0, 0, 0),
	(521, 2, 0, -2.81067, 0),
	(521, 3, 0, -5.65088, 0),
	(521, 4, 0, -8.52051, 0),
	(521, 5, 0, -11.4197, 0),
	(521, 6, 0, -14.3483, 0),
	(521, 7, 0, -17.3064, 0),
	(521, 8, 0, -26.7281, 0),
	(521, 9, 0, -32.3185, 0),
	(521, 10, 0, -32.4275, 0),
	(521, 11, 0, -27.876, 0),
	(521, 12, 0, -22.7274, 0),
	(521, 13, 0, -17.2611, 0),
	(521, 14, 0, -11.2977, 0),
	(521, 15, 0, -4.37378, 0),
	(521, 16, 0, 8.11353, 0),
	(521, 17, 0, 8.46655, 0),
	(521, 18, 0, 5.79175, 0),
	(521, 19, 0, 0.0889893, 0),
	(521, 20, 0, 0, 0),
	(521, 21, 0, 0, 0),
	(527, 0, 0, 0, 0),
	(527, 1, 0, 0, 0),
	(527, 2, 0.0000152588, -5.56274, 0),
	(527, 3, 0.0000152588, -5.56274, 0),
	(529, 0, -0.000511169, -0.212158, 0),
	(529, 1, -0.000511169, -0.212158, 0),
	(529, 2, 0.000328064, 0.0888672, 0),
	(529, 3, 0.0015564, 0.153809, 0),
	(529, 4, 0.00286484, -0.0710449, 0),
	(529, 5, 0.00391769, -0.586426, 0),
	(529, 6, 0.00439453, -1.33716, 0),
	(529, 7, 0.00403976, -2.21875, 0),
	(529, 8, 0.00271988, -3.08984, 0),
	(529, 9, 0.143387, -3.79248, 0),
	(529, 10, 0.3652, -4.17358, 0),
	(529, 11, 0.3652, -4.10938, 0),
	(529, 12, 0.143387, -3.52441, 0),
	(529, 13, -0.0129166, -2.40845, 0),
	(529, 14, 0.143387, -0.823731, 0),
	(529, 15, 0.143387, 1.09766, 0),
	(529, 16, 0.110523, 3.16284, 0),
	(529, 17, 0.110004, 5.13843, 0),
	(529, 18, 0.143387, 6.77637, 0),
	(529, 19, -0.00266647, 7.84351, 0),
	(529, 20, 0.00393295, 8.15112, 0),
	(529, 21, 0.010788, 7.58203, 0),
	(529, 22, 0.010788, 7.58203, 0),
	(532, 0, 5.10928, 13.0106, 0),
	(532, 1, 5.10928, 13.0106, 0),
	(532, 2, 4.80472, 13.4603, 0),
	(532, 3, 4.01797, 13.0189, 0),
	(532, 4, 2.37979, 11.6864, 0),
	(532, 5, 0.574858, 9.46277, 0),
	(532, 6, -1.06357, 6.33972, 0),
	(532, 7, -1.95968, 3.21668, 0),
	(532, 8, -2.57044, 0.984741, 0),
	(532, 9, -2.58411, -0.356079, 0),
	(532, 10, -1.75745, -0.805786, 0),
	(532, 11, -0.348114, -0.364258, 0),
	(532, 12, 0.667755, 0.968262, 0),
	(532, 13, 2.58548, 3.19177, 0),
	(532, 14, 3.56473, 4.55139, 0),
	(532, 15, 4.80606, 6.75623, 0),
	(532, 16, 6.34561, 10.7704, 0),
	(532, 17, 6.04312, 13.8934, 0),
	(532, 18, 6.41477, 16.1254, 0),
	(532, 19, 6.68357, 17.4662, 0),
	(532, 20, 5.10928, 13.0106, 0),
	(532, 21, 5.10928, 13.0106, 0),
	(600, 0, -1.87737, -20.1523, 0),
	(600, 1, -1.87737, -20.1523, 0),
	(600, 2, 0, 0, 0),
	(600, 3, 0, 0, 0),
	(622, 0, 0, 0, 0),
	(622, 1, 0, 0, 0),
	(622, 2, 8.28084, 7.72681, 0),
	(622, 3, 8.28084, 7.72681, 0),
	(775, 0, 0, 0, 0),
	(775, 1, 0, 0, 0),
	(775, 2, 0, 36.4719, 0),
	(775, 3, 0, 36.4719, 0),
	(1067, 0, 0, 0, 0),
	(1067, 1, 0, 0, 0),
	(1067, 2, 0, 3.53552, 0),
	(1067, 3, 0, 7.07107, 0),
	(1067, 4, 0, 10.6066, 0),
	(1067, 5, 0, 14.1421, 0),
	(1067, 6, 0, 17.6777, 0),
	(1067, 7, 0, 21.2132, 0),
	(1067, 8, 0, 24.7488, 0),
	(1067, 9, 0, 28.2843, 0),
	(1067, 10, 0, 31.8198, 0),
	(1067, 11, 0, 35.3554, 0),
	(1067, 12, 0, 35.3554, 0),
	(1068, 0, 0, 0, 0),
	(1068, 1, 0, 0, 0),
	(1068, 2, 0, -18.8814, 0),
	(1068, 3, 0, -18.8814, 0);
/*!40000 ALTER TABLE `areatrigger_move_splines` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;