function [ Label,OutputImg,RegionNum ] = SCoWOverSegmentaion( InputImg,RegionSize )
%SCOWOVERSEGMENTAION Summary of this function goes here
%   Detailed explanation goes here

OutputImg=zeros(size(InputImg),'like',InputImg);

cform = makecform('srgb2lab'); % 转换到Lab颜色空间
LabImg = applycform(InputImg, cform);
LabImg = im2double(LabImg);

L = LabImg(:,:,1);
a= LabImg(:,:,2);
b = LabImg(:,:,3);
st = clock;
[boundary,Label] = SCoW(L,a,b,0.01,RegionSize); %最后一个参数改变区域大小
fprintf(' took %.5f second\n',etime(clock,st));
RegionNum=max(max(Label));
R=InputImg(:,:,1);
G=InputImg(:,:,2);
B=InputImg(:,:,3);
R(boundary>0)=255; %显示区域边界
G(boundary>0)=0;
B(boundary>0)=0;
OutputImg(:,:,1)=R;
OutputImg(:,:,2)=G;
OutputImg(:,:,3)=B;

imshow(OutputImg,[]);

end

