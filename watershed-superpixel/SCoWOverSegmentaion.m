function [ Label,OutputImg,RegionNum ] = SCoWOverSegmentaion( InputImg,RegionSize )
%SCOWOVERSEGMENTAION Summary of this function goes here
%   Detailed explanation goes here

OutputImg=zeros(size(InputImg),'like',InputImg);

cform = makecform('srgb2lab'); % ת����Lab��ɫ�ռ�
LabImg = applycform(InputImg, cform);
LabImg = im2double(LabImg);

L = LabImg(:,:,1);
a= LabImg(:,:,2);
b = LabImg(:,:,3);
st = clock;
[boundary,Label] = SCoW(L,a,b,0.01,RegionSize); %���һ�������ı������С
fprintf(' took %.5f second\n',etime(clock,st));
RegionNum=max(max(Label));
R=InputImg(:,:,1);
G=InputImg(:,:,2);
B=InputImg(:,:,3);
R(boundary>0)=255; %��ʾ����߽�
G(boundary>0)=0;
B(boundary>0)=0;
OutputImg(:,:,1)=R;
OutputImg(:,:,2)=G;
OutputImg(:,:,3)=B;

imshow(OutputImg,[]);

end

