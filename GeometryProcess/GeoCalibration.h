#pragma once
#include "geomodelline.h"
#include "GeoModelArray.h"
#include "GeoBase.h"

class GeoCalibration :
	public GeoModelLine
{
public:
	GeoCalibration(void);
	~GeoCalibration(void);
	GeoBase m_base;
	// �ⷽλԪ�ؼ�У
	void ExtOrientCali(GeoOrbit *orbit, GeoAttitude *att, GeoTime *time, GeoCamera *cam, StrModelParamInput input,vector<StrGCP>ZY3_GCP);
	//����ǰ����֡ƫ�ò�������
	bool calcOffsetMatrix(GeoModelArray* pModel, StrGCP* pGCP, int numGCP, OffsetAngle &angle);
	//����������Ru������ٶ�
	void CalcRealOmega(GeoModelArray *pModel, OffsetAngle Ru, structEOP* Eop, Gyro & omega);
	//����в�
	void calcRMS(GeoModelArray* pModel, string workpath, StrGCP *pGCP, int numGCP);
	//������ʵ���Ƶ����в�
	void calcGCPerr(GeoModelArray* pModel, string strImg, string out, vector<RMS>&acc, bool isPlus1);
};

