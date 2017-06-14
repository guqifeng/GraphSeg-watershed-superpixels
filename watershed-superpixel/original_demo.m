[filename,pathname]=uigetfile({'*.jpg'},'choose the picture');
str=[pathname, filename];
InputImg = imread(str);
[Label,OutputImg,RegionNum]=SCoWOverSegmentaion(InputImg,60);











