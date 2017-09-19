#ifndef _WORKFLOW_ZY3
#define	_WORKFLOW_ZY3

#include "WorkFlow.h"
#include "GeoOrbitEarth_ZY3.h"
#include "GeoAttitude_ZY3.h"
#include "AttDeter.h"
#include "GeoTime_ZY3.h"
#include "GeoCameraLine.h"		// ���������
#include "GeoCameraArray.h"		// ���������
#include "GeoModelLine.h"		// �����������ģ����
#include "GeoModelArray.h"		// �������������
#include "GeoModelRFM.h"		//
#include "ParseZY3Aux.h"
#include "GeoCalibration.h"
#include "GeoReadImage.h"
#include "GeoImage.h"
#include "GeoHarris.h"
#include "LSMatching.h"
#include "PhaseCorrelation.h"
#include <iomanip>

class WorkFlow_ZY3 : public WorkFlow
{
public:
	WorkFlow_ZY3(void);
	virtual ~WorkFlow_ZY3(void);
	
	void GetEOP(string eoppath);
	void GetDEM(string dempath);
	// ����ģ�͹���
	void GenerateRigorousModel(string auxpath, string eoppath);
	//��Уģ�͹���
	void CalibrationModel(string auxpath, string eoppath);
	void CalibrationModel2(string auxpath, string eoppath);
	//������֤
	void AccuracyVerify(string auxpath);
	//��ȡ���Ƶ�
	void GetGCP(string auxpath, vector<StrGCP> &ZY3_GCP);

	//////////////////////////////////////////////////////////////////////////
	//С������غ���
	//////////////////////////////////////////////////////////////////////////
	//�����������
	void SetCamInput(StrCamParamInput caminput);
	//ģ�ͽ�����֤
	void ModelVerify();
	//�������ģ��
	void NADCamera(string auxpath);
	//���ǰ������ʵģ��
	GeoModelLine FwdBwdModel(string workpath,double omg, bool isReal);
	GeoModelLine FwdBwdModelVerify(string workpath, double omg, bool isReal);
	//�õ���ɨ�����ʵ���Ƶ�
	void CalcFwdBwdRealMatchPoint(char* argv[]);	
	//ǰ�������ǰ������
	void CalcFwdBwdIntersection(char* argv[]);
	//��ǰ����·������Ԫ���Ĺ���
	void ChangeAttPath(char* argv[]);
	//��������ƽ��
	void Calc3DAccuracyByAdjustment(char* argv[]);
	//���ƥ���Ϳ��Ƶ�
	void OutputMatchAndGCP(string filePath, vector<MatchPoint>pMatch, vector<StrGCP>pGCP);
	void OutputPxyAndGCP(string filePath, vector<MatchPoint>pMatch, vector<StrGCP>pGCP);
	//����ǰ���ӵ�rpc�ļ�
	void CalcFwdBwdRPC(char* argv[]);

	//С���������ģ��
	void LittleArrayCamera(string auxpath);
	//����RPCƥ��
	int Image_registration_rpc(string tifPath);
	//ƥ�����
	void MatchBasedGeoModel(MatchPoint *gcp, int num, string imgL, string imgR);
	//������ʵƥ����Ƶ�
	void CalcRealMatchPoint(string workpath);
	//����ָ�����̬�����㲢�Ƚϣ�
	void CalcRealAttitude(string workpath);
	//����ָ�����̬�������㣩
	void CalcModifyAttitude(string workpath);
	//�ں�����RU
	void RuFusion(vector<OffsetAngle>&RuForward, vector<OffsetAngle>RuBackward);
	//����ģ�ͼ���в�
	void CalcRMS(string out,StrGCP *pGCP,int num);
	//�Ա�
	void CompareMeasModifyAndReal(vector<Attitude>Meas, vector<Attitude>Modify, string realAttPath);
	//�Ա�RMS
	void OutputRMS(string outFile, vector<strRMS>accuracy1, vector<strRMS>accuracy2);
	//�����Ԫ�����
	void OutputQuat(string path,vector<Attitude>att);

	//����ƥ�������ٶȣ�Ȼ������ʵ��̬���������˲�
	void CalcOmegaKalman(string workpath);
	//����ϡ�����Լ����̬
	void CalcRealAttitude_sparse(string workpath);
	//ϡ��������
	bool autoGeoCalibration_sparse(GeoModelArray *pGeoModel, int num, 
		conjugatePoints* pMatch,int nMatch, int xOrder, int yOrder, double *&pRes, string sRes);
private:
	string sEOP,sDEM;
	static int outCount;
	StrCamParamInput CameraInput;
	//GeoModelArray *pModelArray;
};

#endif


