-- Pathing for Ironforge Mountaineer Entry: 727
SET @NPC := 167427;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-5347.861,`position_y`=-522.5091,`position_z`=391.5905 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,258,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-5347.861,-522.5091,391.5905,0,0,0,0,100,0),
(@PATH,2,-5366.906,-521.4763,391.6183,0,0,0,0,100,0),
(@PATH,3,-5399.757,-516.5439,391.9933,0,0,0,0,100,0),
(@PATH,4,-5433.19,-516.805,395.9774,0,0,0,0,100,0),
(@PATH,5,-5466.6,-520.7313,397.498,0,0,0,0,100,0),
(@PATH,6,-5507.277,-514.5727,397.5857,0,0,0,0,100,0),
(@PATH,7,-5521.092,-494.6748,397.5857,0,0,0,0,100,0),
(@PATH,8,-5533.865,-484.724,397.5856,0,0,0,0,100,0),
(@PATH,9,-5562.226,-479.3515,397.5856,0,0,0,0,100,0),
(@PATH,10,-5588.652,-484.579,397.1053,0,0,0,0,100,0),
(@PATH,11,-5610.264,-482.2413,397.0437,0,0,0,0,100,0),
(@PATH,12,-5623.959,-485.3744,397.0437,0,0,0,0,100,0),
(@PATH,13,-5646.115,-484.474,396.403,0,0,0,0,100,0),
(@PATH,14,-5684.308,-482.6571,396.0274,0,0,0,0,100,0),
(@PATH,15,-5646.115,-484.474,396.403,0,0,0,0,100,0),
(@PATH,16,-5623.959,-485.3744,397.0437,0,0,0,0,100,0),
(@PATH,17,-5610.264,-482.2413,397.0437,0,0,0,0,100,0),
(@PATH,18,-5588.652,-484.579,397.1053,0,0,0,0,100,0),
(@PATH,19,-5562.226,-479.3515,397.5856,0,0,0,0,100,0),
(@PATH,20,-5533.865,-484.724,397.5856,0,0,0,0,100,0),
(@PATH,21,-5521.092,-494.6748,397.5857,0,0,0,0,100,0),
(@PATH,22,-5507.277,-514.5727,397.5857,0,0,0,0,100,0),
(@PATH,23,-5466.6,-520.7313,397.498,0,0,0,0,100,0),
(@PATH,24,-5433.19,-516.805,395.9774,0,0,0,0,100,0),
(@PATH,25,-5399.757,-516.5439,391.9933,0,0,0,0,100,0),
(@PATH,26,-5366.906,-521.4763,391.6183,0,0,0,0,100,0);

-- Pathing for Ironforge Mountaineer Entry: 727
SET @NPC := 167425;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-5237.249,`position_y`=-572.7875,`position_z`=405.5655 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,258,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-5237.249,-572.7875,405.5655,0,0,1,0,100,0),
(@PATH,2,-5242.318,-566.8207,403.418,0,0,1,0,100,0),
(@PATH,3,-5242.512,-533.8203,391.5114,0,0,1,0,100,0),
(@PATH,4,-5247.748,-515.876,386.3603,0,30000,1,0,100,0),
(@PATH,5,-5243.176,-543.9634,395.1508,0,0,0,0,100,0),
(@PATH,6,-5242.821,-564.1043,402.526,0,0,0,0,100,0),
(@PATH,7,-5239.889,-571.1794,404.9868,0,0,0,0,100,0),
(@PATH,8,-5232.076,-573.5452,405.5548,0,0,0,0,100,0),
(@PATH,9,-5227.861,-572.004,404.7089,0,0,0,0,100,0),
(@PATH,10,-5226.727,-562.0967,408.5596,0,0,0,0,100,0),
(@PATH,11,-5226.727,-562.0967,408.5596,0,0,0,0,100,0),
(@PATH,12,-5226.727,-562.0967,408.5596,2.199115,54000,0,0,100,0);

-- Pathing for Ironforge Mountaineer Entry: 727
SET @NPC := 167841;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-5261.726,`position_y`=-489.1352,`position_z`=386.8289 WHERE `guid`=@NPC;
UPDATE `creature` SET `spawndist`=0,`MovementType`=0,`position_x`=-5261.726,`position_y`=-489.1352,`position_z`=386.8289 WHERE `guid`=167843;
DELETE FROM `creature_addon` WHERE `guid` IN (@NPC,167843);
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,258,0, ''),(167843,0,0,0,258,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-5261.726,-489.1352,386.8289,0,0,0,0,100,0),
(@PATH,2,-5295.799,-507.9429,391.6417,0,0,0,0,100,0),
(@PATH,3,-5333.296,-517.0845,391.5824,0,0,0,0,100,0),
(@PATH,4,-5352.134,-533.1839,391.5905,0,0,0,0,100,0),
(@PATH,5,-5357.62,-566.5634,391.6183,0,0,0,0,100,0),
(@PATH,6,-5379.194,-600.0013,391.5752,0,0,0,0,100,0),
(@PATH,7,-5395.071,-633.5403,391.7674,0,0,0,0,100,0),
(@PATH,8,-5408.498,-666.6967,393.0878,0,0,0,0,100,0),
(@PATH,9,-5424.699,-700.179,393.6027,0,0,0,0,100,0),
(@PATH,10,-5439.374,-733.2343,393.8118,0,0,0,0,100,0),
(@PATH,11,-5442.045,-766.761,394.2389,0,0,0,0,100,0),
(@PATH,12,-5424.216,-800.1314,392.3553,0,0,0,0,100,0),
(@PATH,13,-5398.037,-833.3683,392.3146,0,0,0,0,100,0),
(@PATH,14,-5384.929,-866.7958,392.0685,0,0,0,0,100,0),
(@PATH,15,-5390.577,-899.8145,392.3146,0,0,0,0,100,0),
(@PATH,16,-5407.956,-920.0989,392.2308,0,0,0,0,100,0),
(@PATH,17,-5425.412,-966.9361,392.3169,0,0,0,0,100,0),
(@PATH,18,-5450.83,-979.2663,392.3313,0,0,0,0,100,0),
(@PATH,19,-5466.885,-1000.967,392.2427,0,0,0,0,100,0),
(@PATH,20,-5499.975,-1012.016,393.2427,0,0,0,0,100,0),
(@PATH,21,-5533.405,-1019.367,392.9933,0,0,0,0,100,0),
(@PATH,22,-5566.401,-1014.023,392.8988,0,0,0,0,100,0),
(@PATH,23,-5533.405,-1019.367,392.9933,0,0,0,0,100,0),
(@PATH,24,-5499.975,-1012.016,393.2427,0,0,0,0,100,0),
(@PATH,25,-5466.885,-1000.967,392.2427,0,0,0,0,100,0),
(@PATH,26,-5450.83,-979.2663,392.3313,0,0,0,0,100,0),
(@PATH,27,-5425.412,-966.9361,392.3169,0,0,0,0,100,0),
(@PATH,28,-5407.956,-920.0989,392.2308,0,0,0,0,100,0),
(@PATH,29,-5390.577,-899.8145,392.3146,0,0,0,0,100,0),
(@PATH,30,-5384.929,-866.7958,392.0685,0,0,0,0,100,0),
(@PATH,31,-5398.037,-833.3683,392.3146,0,0,0,0,100,0),
(@PATH,32,-5424.216,-800.1314,392.3553,0,0,0,0,100,0),
(@PATH,33,-5442.045,-766.761,394.2389,0,0,0,0,100,0),
(@PATH,34,-5439.374,-733.2343,393.8118,0,0,0,0,100,0),
(@PATH,35,-5424.699,-700.179,393.6027,0,0,0,0,100,0),
(@PATH,36,-5408.498,-666.6967,393.0878,0,0,0,0,100,0),
(@PATH,37,-5395.071,-633.5403,391.7674,0,0,0,0,100,0),
(@PATH,38,-5379.194,-600.0013,391.5752,0,0,0,0,100,0),
(@PATH,39,-5357.62,-566.5634,391.6183,0,0,0,0,100,0),
(@PATH,40,-5352.134,-533.1839,391.5905,0,0,0,0,100,0),
(@PATH,41,-5333.296,-517.0845,391.5824,0,0,0,0,100,0),
(@PATH,42,-5295.834,-507.291,391.5833,0,0,0,0,100,0);
-- Set Formation/Group Combat Assistance
DELETE FROM `creature_formations` WHERE `leaderGUID`=167841;
INSERT INTO `creature_formations` (`leaderGUID`,`memberGUID`,`dist`,`angle`,`groupAI`) VALUES
(167841,167841,0,0,2),
(167841,167843,2,80,2);

-- Pathing for Ironforge Mountaineer Entry: 727
SET @NPC := 169359;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4671.61,`position_y`=-1650.729,`position_z`=503.7488 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,258,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4671.61,-1650.729,503.7488,0,0,1,0,100,0),
(@PATH,2,-4653.098,-1650.523,504.1336,0,0,1,0,100,0),
(@PATH,3,-4626.28,-1651.301,504.2564,0,0,1,0,100,0),
(@PATH,4,-4611.057,-1648.403,503.5677,0,0,1,0,100,0),
(@PATH,5,-4599.792,-1641.667,503.4365,0,0,1,0,100,0),
(@PATH,6,-4585.354,-1633.899,503.4365,0,0,1,0,100,0),
(@PATH,7,-4573.834,-1631.895,503.4409,0,0,1,0,100,0),
(@PATH,8,-4562.141,-1632.032,503.6202,0,0,1,0,100,0),
(@PATH,9,-4585.354,-1633.899,503.4365,0,0,1,0,100,0),
(@PATH,10,-4599.792,-1641.667,503.4365,0,0,1,0,100,0),
(@PATH,11,-4611.057,-1648.403,503.5677,0,0,1,0,100,0),
(@PATH,12,-4626.28,-1651.301,504.2564,0,0,1,0,100,0),
(@PATH,13,-4653.098,-1650.523,504.1336,0,0,1,0,100,0),
(@PATH,14,-4671.61,-1650.729,503.7488,0,0,1,0,100,0),
(@PATH,15,-4698.264,-1650.24,503.5403,0,0,1,0,100,0),
(@PATH,16,-4723,-1651.537,503.7784,0,0,1,0,100,0),
(@PATH,17,-4735.43,-1654.646,504.0691,0,0,1,0,100,0),
(@PATH,18,-4742.155,-1652.394,503.6739,0,0,1,0,100,0),
(@PATH,19,-4746.222,-1648.006,503.449,0,0,1,0,100,0),
(@PATH,20,-4723,-1651.537,503.7784,0,0,1,0,100,0),
(@PATH,21,-4698.264,-1650.24,503.5403,0,0,1,0,100,0);

-- Pathing for Ironforge Guard Entry: 5595
SET @NPC := 167491;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-5203.363,`position_y`=-699.6258,`position_z`=438.4007 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,257,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-5203.363,-699.6258,438.4007,0,0,0,0,100,0),
(@PATH,2,-5218.088,-666.4339,430.14,0,0,0,0,100,0),
(@PATH,3,-5228.595,-633.1194,421.741,0,0,0,0,100,0),
(@PATH,4,-5237.807,-599.4499,413.6968,0,0,0,0,100,0),
(@PATH,5,-5241.627,-566.6175,403.4313,0,0,0,0,100,0),
(@PATH,6,-5243.015,-532.7789,391.0985,0,0,0,0,100,0),
(@PATH,7,-5256.577,-498.8654,386.2344,0,0,0,0,100,0),
(@PATH,8,-5243.385,-533.1536,391.2333,0,0,0,0,100,0),
(@PATH,9,-5242.362,-566.6934,403.3719,0,0,0,0,100,0),
(@PATH,10,-5238.352,-599.8167,413.7559,0,0,0,0,100,0),
(@PATH,11,-5229.088,-633.2765,421.6609,0,0,0,0,100,0),
(@PATH,12,-5218.85,-666.7302,430.0223,0,0,0,0,100,0),
(@PATH,13,-5204.014,-699.4961,438.3316,0,0,0,0,100,0),
(@PATH,14,-5188.978,-733.1346,447.0623,0,0,0,0,100,0),
(@PATH,15,-5166.568,-740.9424,450.8019,0,0,0,0,100,0),
(@PATH,16,-5133.428,-742.4106,459.3805,0,0,0,0,100,0),
(@PATH,17,-5100.03,-742.1588,467.9603,0,0,0,0,100,0),
(@PATH,18,-5066.893,-749.7949,479.0317,0,0,0,0,100,0),
(@PATH,19,-5054.69,-766.5782,488.9085,0,0,0,0,100,0),
(@PATH,20,-5050.706,-799.8795,495.2132,0,0,0,0,100,0),
(@PATH,21,-5050.173,-811.2641,495.2521,0,0,0,0,100,0),
(@PATH,22,-5045.451,-815.5643,495.2521,0,0,0,0,100,0),
(@PATH,23,-5050.712,-810.2087,495.2521,0,0,0,0,100,0),
(@PATH,24,-5050.712,-810.2087,495.2521,4.729842,40000,0,0,100,0),
(@PATH,25,-5045.773,-786.9305,495.2132,0,0,0,0,100,0),
(@PATH,26,-5061.846,-752.7072,481.8096,0,0,0,0,100,0),
(@PATH,27,-5097.768,-740.2383,468.6567,0,0,0,0,100,0),
(@PATH,28,-5133.368,-741.2177,459.3947,0,0,0,0,100,0),
(@PATH,29,-5166.305,-739.1543,450.9035,0,0,0,0,100,0),
(@PATH,30,-5187.297,-733.2242,447.4483,0,0,0,0,100,0);


-- Pathing for Mounted Ironforge Mountaineer Entry: 12996
SET @NPC := 181037;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4668.872,`position_y`=-1640.948,`position_z`=503.449 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,2786,0,257,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4668.872,-1640.948,503.449,0,0,0,0,100,0),
(@PATH,2,-4715.474,-1640.861,503.4064,0,0,0,0,100,0),
(@PATH,3,-4744.719,-1654.845,503.968,0,0,0,0,100,0),
(@PATH,4,-4768.215,-1669.226,503.449,0,0,0,0,100,0),
(@PATH,5,-4763.347,-1687.615,503.449,0,0,0,0,100,0),
(@PATH,6,-4740.479,-1690.502,503.449,0,0,0,0,100,0),
(@PATH,7,-4714.059,-1691.837,503.449,0,0,0,0,100,0),
(@PATH,8,-4690.993,-1692.033,503.449,0,0,0,0,100,0),
(@PATH,9,-4665.583,-1691.689,503.449,0,0,0,0,100,0),
(@PATH,10,-4642.208,-1693.22,503.449,0,0,0,0,100,0),
(@PATH,11,-4632.467,-1677.46,504.7161,0,0,0,0,100,0),
(@PATH,12,-4630.139,-1652.125,504.6363,0,0,0,0,100,0),
(@PATH,13,-4641.202,-1640.951,503.449,0,0,0,0,100,0);

-- Pathing for Mounted Ironforge Mountaineer Entry: 12996
SET @NPC := 180896;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4517.085,`position_y`=-1704.979,`position_z`=507.9045 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,2786,0,257,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4517.085,-1704.979,507.9045,0,0,0,0,100,0),
(@PATH,2,-4522.742,-1694.59,506.6701,0,0,0,0,100,0),
(@PATH,3,-4527.538,-1678.833,504.6588,0,0,0,0,100,0),
(@PATH,4,-4522.392,-1665.245,504.6862,0,0,0,0,100,0),
(@PATH,5,-4509.5,-1639.036,504.9057,0,0,0,0,100,0),
(@PATH,6,-4495.567,-1632.198,503.3942,0,0,0,0,100,0),
(@PATH,7,-4481.475,-1624.604,499.0314,0,0,0,0,100,0),
(@PATH,8,-4476.082,-1615.97,496.0509,0,0,0,0,100,0),
(@PATH,9,-4471.422,-1606.708,493.3136,0,0,0,0,100,0),
(@PATH,10,-4460.788,-1594.323,489.9431,0,0,0,0,100,0),
(@PATH,11,-4451.252,-1580.116,487.9648,0,0,0,0,100,0),
(@PATH,12,-4438.871,-1565.696,483.9018,0,0,0,0,100,0),
(@PATH,13,-4425,-1556.512,479.425,0,0,0,0,100,0),
(@PATH,14,-4414.128,-1543.695,477.4777,0,0,0,0,100,0),
(@PATH,15,-4408.502,-1528.727,478.1522,0,0,0,0,100,0),
(@PATH,16,-4404.448,-1517.266,479.7303,0,0,0,0,100,0),
(@PATH,17,-4398.092,-1508.633,479.3889,0,0,0,0,100,0),
(@PATH,18,-4389.52,-1515.529,470.3234,0,0,0,0,100,0),
(@PATH,19,-4398.092,-1508.633,479.3889,0,0,0,0,100,0),
(@PATH,20,-4404.448,-1517.266,479.7303,0,0,0,0,100,0),
(@PATH,21,-4408.401,-1528.423,477.8348,0,0,0,0,100,0),
(@PATH,22,-4414.128,-1543.695,477.4777,0,0,0,0,100,0),
(@PATH,23,-4425,-1556.512,479.425,0,0,0,0,100,0),
(@PATH,24,-4438.871,-1565.696,483.9018,0,0,0,0,100,0),
(@PATH,25,-4451.266,-1580.094,488.1284,0,0,0,0,100,0),
(@PATH,26,-4460.788,-1594.323,489.9431,0,0,0,0,100,0),
(@PATH,27,-4471.422,-1606.708,493.3136,0,0,0,0,100,0),
(@PATH,28,-4476.082,-1615.97,496.0509,0,0,0,0,100,0),
(@PATH,29,-4481.316,-1624.484,499.0314,0,0,0,0,100,0),
(@PATH,30,-4495.379,-1632.109,503.2814,0,0,0,0,100,0),
(@PATH,31,-4509.5,-1639.036,504.9057,0,0,0,0,100,0),
(@PATH,32,-4522.392,-1665.245,504.6862,0,0,0,0,100,0),
(@PATH,33,-4527.538,-1678.833,504.6588,0,0,0,0,100,0),
(@PATH,34,-4522.742,-1694.59,506.6701,0,0,0,0,100,0);

-- Pathing for Mounted Ironforge Mountaineer Entry: 12996
SET @NPC := 169657;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-4652.451,`position_y`=-1631.388,`position_z`=503.4637 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,2786,0,257,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-4652.451,-1631.388,503.4637,0,0,0,0,100,0),
(@PATH,2,-4632.746,-1633.525,503.4468,0,0,0,0,100,0),
(@PATH,3,-4612.11,-1631.77,503.5919,0,0,0,0,100,0),
(@PATH,4,-4586.936,-1630.191,503.3159,0,0,0,0,100,0),
(@PATH,5,-4575.135,-1625.416,503.4409,0,0,0,0,100,0),
(@PATH,6,-4561.062,-1619.17,504.1121,0,0,0,0,100,0),
(@PATH,7,-4547.249,-1607.701,503.5308,0,0,0,0,100,0),
(@PATH,8,-4533.738,-1600.054,504.1653,0,0,0,0,100,0),
(@PATH,9,-4521.967,-1601.77,503.9267,0,0,0,0,100,0),
(@PATH,10,-4518.593,-1613.957,504.414,0,0,0,0,100,0),
(@PATH,11,-4519.591,-1625.009,504.6767,0,0,0,0,100,0),
(@PATH,12,-4527.155,-1634.56,504.5781,0,0,0,0,100,0),
(@PATH,13,-4537.003,-1633.534,504.4876,0,0,0,0,100,0),
(@PATH,14,-4544.92,-1630.185,505.3416,0,0,0,0,100,0),
(@PATH,15,-4552.14,-1627.614,505.137,0,0,0,0,100,0),
(@PATH,16,-4558.058,-1630.405,503.9405,0,0,0,0,100,0),
(@PATH,17,-4563.645,-1636.717,503.449,0,0,0,0,100,0),
(@PATH,18,-4568.632,-1642.606,503.4365,0,0,0,0,100,0),
(@PATH,19,-4573.396,-1648.352,503.4316,0,0,0,0,100,0),
(@PATH,20,-4584.838,-1650.11,503.9629,0,0,0,0,100,0),
(@PATH,21,-4604.959,-1652.265,504.2403,0,0,0,0,100,0),
(@PATH,22,-4627.976,-1649.708,503.8765,0,0,0,0,100,0),
(@PATH,23,-4652.892,-1650.043,504.0513,0,0,0,0,100,0),
(@PATH,24,-4673.2,-1652.772,504.1424,0,0,0,0,100,0),
(@PATH,25,-4684.272,-1651.478,503.689,0,0,0,0,100,0),
(@PATH,26,-4707.206,-1649.057,503.4806,0,0,0,0,100,0),
(@PATH,27,-4719.713,-1652.222,504.1901,0,0,0,0,100,0),
(@PATH,28,-4736.423,-1656.21,504.2566,0,0,0,0,100,0),
(@PATH,29,-4748.86,-1658.799,504.5674,0,0,0,0,100,0),
(@PATH,30,-4754.425,-1665.556,503.9805,0,0,0,0,100,0),
(@PATH,31,-4766.01,-1673.682,503.449,0,0,0,0,100,0),
(@PATH,32,-4780.701,-1676.232,503.449,0,0,0,0,100,0),
(@PATH,33,-4791.706,-1669.026,503.3911,0,0,0,0,100,0),
(@PATH,34,-4791.838,-1658.466,504.4534,0,0,0,0,100,0),
(@PATH,35,-4785.26,-1648.255,505.0581,0,0,0,0,100,0),
(@PATH,36,-4777.67,-1640.852,503.9646,0,0,0,0,100,0),
(@PATH,37,-4765.703,-1633.394,503.574,0,0,0,0,100,0),
(@PATH,38,-4758.079,-1632.184,503.6323,0,0,0,0,100,0),
(@PATH,39,-4745.59,-1631.477,504.0027,0,0,0,0,100,0),
(@PATH,40,-4733.111,-1631.409,503.7911,0,0,0,0,100,0),
(@PATH,41,-4720.28,-1632.544,503.212,0,0,0,0,100,0),
(@PATH,42,-4707.013,-1631.789,503.462,0,0,0,0,100,0),
(@PATH,43,-4694.465,-1633.212,503.6198,0,0,0,0,100,0),
(@PATH,44,-4671.129,-1631.671,503.507,0,0,0,0,100,0);


-- Pathing for Ironforge Mountaineer Entry: 727
SET @NPC := 167982;
SET @PATH := @NPC * 10;
UPDATE `creature` SET `spawndist`=0,`MovementType`=2,`position_x`=-5719.586,`position_y`=-550.4644,`position_z`=398.7685 WHERE `guid`=@NPC;
DELETE FROM `creature_addon` WHERE `guid`=@NPC;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@NPC,@PATH,0,0,258,0, '');
DELETE FROM `waypoint_data` WHERE `id`=@PATH;
INSERT INTO `waypoint_data` (`id`,`point`,`position_x`,`position_y`,`position_z`,`orientation`,`delay`,`move_type`,`action`,`action_chance`,`wpguid`) VALUES
(@PATH,1,-5719.586,-550.4644,398.7685,0,0,0,0,100,0),
(@PATH,2,-5712.108,-554.6284,398.4516,0,0,0,0,100,0),
(@PATH,3,-5704.653,-558.712,399.4442,0,0,0,0,100,0),
(@PATH,4,-5694.355,-562.8688,400.0139,0,0,0,0,100,0),
(@PATH,5,-5688.045,-570.8251,401.376,0,0,0,0,100,0),
(@PATH,6,-5683.653,-570.796,401.3057,0,0,0,0,100,0),
(@PATH,7,-5689.913,-561.7245,399.6221,0,0,0,0,100,0),
(@PATH,8,-5701.13,-556.4327,399.5258,0,0,0,0,100,0),
(@PATH,9,-5710.505,-551.1133,398.599,0,0,0,0,100,0),
(@PATH,10,-5718.614,-546.7613,398.9713,0,0,0,0,100,0),
(@PATH,11,-5710.505,-551.1133,398.599,0,0,0,0,100,0),
(@PATH,12,-5701.13,-556.4327,399.5258,0,0,0,0,100,0),
(@PATH,13,-5689.913,-561.7245,399.6221,0,0,0,0,100,0),
(@PATH,14,-5683.653,-570.796,401.3057,0,0,0,0,100,0),
(@PATH,15,-5688.045,-570.8251,401.376,0,0,0,0,100,0),
(@PATH,16,-5694.256,-562.9922,400.1756,0,0,0,0,100,0),
(@PATH,17,-5704.653,-558.712,399.4442,0,0,0,0,100,0),
(@PATH,18,-5712.108,-554.6284,398.4516,0,0,0,0,100,0);









