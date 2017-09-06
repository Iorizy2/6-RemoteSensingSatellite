#include "WorkFlow_ZY3.h"

WorkFlow_ZY3::WorkFlow_ZY3(void)
{
}


WorkFlow_ZY3::~WorkFlow_ZY3(void)
{
}

//��ȡEOP·��
void WorkFlow_ZY3::getEOP(string eoppath)
{
	sEOP = eoppath;
}
//////////////////////////////////////////////////////////////////////////
// ����ģ�͹���
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////
// ���ܣ�����ģ�͹���
// ����:
//		string auxpath��	�����ļ�·��
//		string eoppath:		EOP�ļ�·��
// ����ֵ��
//		void
//////////////////////////////////////
void WorkFlow_ZY3::GenerateRigorousModel(string auxpath, string eoppath)
{
	//����ZY302���ݽ���
	ParseZY3Aux ZY3_02;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sInput;
	ZY3_02.ZY302PATH(auxpath, sAtt, sOrb, sTime);
	ZY3_02.ReadZY302OrbTXT(sOrb, allEp);//���ܹ������
	//ZY3_02.ReadZY302OrbTXT2(sOrb, allEp);//���Ϲ������
	ZY3_02.ReadZY302AttTXT(sAtt, allAtt);
	ZY3_02.ReadZY302TimeTXT(sTime, allTime);

	//��ȡZY301��������
	/*ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb,sAtt,sTime,sInput;
	ZY3_01.ZY301PATH(auxpath,sAtt,sOrb,sTime,sInput);
	ZY3_01.ReadZY301OrbTXT(sOrb,allEp);
	ZY3_01.ReadZY301AttTXT(sAtt,allAtt);
	ZY3_01.ReadZY301TimeTXT(sTime,sInput,allTime);*/

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = eoppath;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraLine();
	StrCamParamInput caminput;
	caminput.f = 1.699712;
	caminput.Xsize = 7. / 1e6;
	caminput.Ysize = 7. / 1e6;
	caminput.Xnum = 1;
	caminput.Ynum = 8192 * 3;
	caminput.Xstart = 0.0;
	caminput.Ystart = -12290.48;
	//inner->InitInnerFile("", caminput);
	inner->ReadCamFile("E:\\2_ImageData\\ZY3-02\\1-��λ����\\503\\�궨����\\2016-07-02.cbr", caminput);//��ȡ�ڷ�λԪ��

	// ģ��
	GeoModelLine *model = new GeoModelLine();
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;
	//model->InitExtFile("D:\\2_ImageData\\ZY3-01\\5-����ģ��\\381����\\Ru.txt");//��ȡ�ⷽλԪ��
	model->InitExtFile("E:\\2_ImageData\\ZY3-02\\1-��λ����\\503\\�궨����\\2016-07-02GZC.txt");
	model->InitModelLine(orbit, attitude, time, inner, modelinput);
	pModel = model;
}

/////////////////////////////////////////////
//���ܣ���Уģ��
//���룺��������·����EOP�ļ�·��
//���������Ru�������ģ��
//ע�⣺
//���ڣ�2016.12.20
////////////////////////////////////////////
void WorkFlow_ZY3::CalibrationModel(string auxpath, string eoppath)
{
	//����ZY302���ݽ���
	/*ParseZY3Aux ZY3_02;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	ZY3_02.getZY302Aux(auxpath,allEp,allAtt,allTime);*/

	//��ȡZY301��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sInput;
	ZY3_01.ZY301PATH(auxpath, sAtt, sOrb, sTime, sInput);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadZY301TimeTXT(sTime, sInput, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = eoppath;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraLine();
	StrCamParamInput caminput;
	caminput.f = 1.699712;
	caminput.Xsize = 7. / 1e6;
	caminput.Ysize = 7. / 1e6;
	caminput.Xnum = 1;
	caminput.Ynum = 8192 * 3;
	caminput.Xstart = 0.0;
	caminput.Ystart = -12290.48;
	//inner->InitInnerFile("", caminput);
	inner->ReadCamFile("D:\\2_ImageData\\ZY3-01\\3-Ӱ������\\�궨�������\\381ƽ������\\inner_forhwc.cbr", caminput);//��ȡ�ڷ�λԪ��

	//��ȡ���Ƶ�
	vector<StrGCP> ZY3_GCP;
	GetGCP(auxpath, ZY3_GCP);

	// ģ��
	GeoCalibration *model = new GeoCalibration();
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;
	model->ExtOrientCali(orbit, attitude, time, inner, modelinput, ZY3_GCP);
	pModel = model;
}

/////////////////////////////////////////////
//���ܣ���Уģ��
//���룺��������·����EOP�ļ�·��
//���������Ru�������ģ��
//ע�⣺
//���ڣ�2016.12.20; 2017.04.25
////////////////////////////////////////////
void WorkFlow_ZY3::CalibrationModel2(string auxpath, string eoppath)
{
	//����ZY302���ݽ���
	ParseZY3Aux ZY3_02;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sInput;
	ZY3_02.ZY302PATH(auxpath, sAtt, sOrb, sTime);
	ZY3_02.ReadZY302OrbTXT(sOrb, allEp);
	ZY3_02.ReadZY302AttTXT(sAtt, allAtt);
	ZY3_02.ReadZY302TimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = eoppath;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraLine();
	StrCamParamInput caminput;
	//caminput.f = 1.699712;
	//caminput.Xsize = 7. / 1e6;
	//caminput.Ysize = 7. / 1e6;
	//caminput.Xnum = 1;
	//caminput.Ynum = 8192 * 3;
	//caminput.Xstart = 0.0;
	//caminput.Ystart = -12290.48;
	//inner->InitInnerFile("", caminput);
	inner->ReadCamFile("D:\\2_ImageData\\ZY3-02\\1-��λ����\\503\\�궨����\\2016-07-02.cbr", caminput);//��ȡ�ڷ�λԪ��

	//��ȡ���Ƶ�
	vector<StrGCP> ZY3_GCP;
	GetGCP(auxpath, ZY3_GCP);

	// ģ��
	GeoCalibration *model = new GeoCalibration();
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;
	model->ExtOrientCali(orbit, attitude, time, inner, modelinput, ZY3_GCP);
	pModel = model;
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�������Ŀ��Ƶ���о�����֤
//���룺��������·����EOP�ļ�·��
//�����������֤���
//ע�⣺��������ĵ���Ҫ�����ܼ���ģ�͹����Ժ�
//���ߣ�GZC
//���ڣ�2017.04.26
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::AccuracyVerify(string auxpath)
{
	string gcppath = auxpath + "\\GCP.txt";
	FILE *fp = fopen(gcppath.c_str(), "r");
	int m;
	fscanf(fp, "%d\n", &m);
	double lat, lon, h, xr, yr;
	double *x = new double[m];
	double *y = new double[m];
	double *xErr = new double[m];
	double *yErr = new double[m];
	double xErrSum = 0, yErrSum = 0;
	for (int i = 0; i < m; i++)
	{
		fscanf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\n", &x[i], &y[i], &lat, &lon, &h);
		pModel->FromLatLon2XY(lat / 180 * PI, lon / 180 * PI, h, yr, xr);
		xErr[i] = x[i] - xr;
		yErr[i] = y[i] - yr;
		xErrSum += xErr[i] * xErr[i];
		yErrSum += yErr[i] * yErr[i];
	}
	double xxErr = sqrt(xErrSum / m);
	double yyErr = sqrt(yErrSum / m);
	double zzErr = sqrt(xxErr*xxErr + yyErr*yyErr);

	string errorpath = auxpath + "\\Acurracy.txt";
	FILE *fperr = fopen(errorpath.c_str(), "w");
	for (int i = 0; i < m; i++)
	{
		fprintf(fperr, "%.2f\t%.2f\t%.9f\t%.9f\n", x[i], y[i], xErr[i], yErr[i]);
	}
	fprintf(fperr, "\n");
	fprintf(fperr, "%.9f\t%.9f\t%.9f\n", xxErr, yyErr, zzErr);
	fcloseall;
}

/////////////////////////////////////////////
//���ܣ���ȡ���Ƶ�
//���룺auxpath:���GCP���ݵ�·��
//�������ȡ�����������Ƶ�
//ע�⣺
//���ڣ�2016.12.20
////////////////////////////////////////////
void WorkFlow_ZY3::GetGCP(string auxpath, vector<StrGCP> &ZY3_GCP)
{
	string gcppath = auxpath + "\\GCP.txt";
	FILE *fp = fopen(gcppath.c_str(), "r");
	int m;
	fscanf(fp, "%d\n", &m);
	StrGCP GCP_tmp;
	for (int i = 0; i < m; i++)
	{
		fscanf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\n", &GCP_tmp.x, &GCP_tmp.y, &GCP_tmp.lat, &GCP_tmp.lon, &GCP_tmp.h);
		ZY3_GCP.push_back(GCP_tmp);
	}
}

//////////////////////////////////////////////////////////////////////////
//���ܣ����������x��y�鿴ģ�ͽ������Ƿ�׼ȷ
//���룺
//�����
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.14
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::ModelVerify()
{
	double lat, lon, h = 0, x = 1, y = 1;
	while (x != 0 || y != 0)
	{
		cout << "������Sample��Line��h(��������0�������˳�)" << endl;
		cin >> x >> y >> h;
		pModel->FromXY2LatLon(x, y, h, lat, lon);
		lat = lat * 180 / PI;
		lon = lon * 180 / PI;
		cout << "��γ�ȷֱ���" << endl;
		cout << setiosflags(ios::fixed);//������仰�����Ƶľ���С���ľ�����
		cout << setprecision(10) << lat << "," << lon << endl;
	}
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�NAD���ģ��
//���룺��������·����EOP�ļ�·��
//���������ģ��
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.14
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::NADCamera(string auxpath)
{
	//��ȡZY3Sim��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sCam;
	ZY3_01.ZY3SimPATH(auxpath, sAtt, sOrb, sTime, sCam);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadZY3SimTimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = sEOP;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraLine();
	StrCamParamInput caminput;
	//caminput.f = 1.7;
	//caminput.Xsize = 1. / 1e6;
	//caminput.Ysize = 1. / 1e6;
	//caminput.Xnum = 1;
	//caminput.Ynum = 1000;
	//caminput.Xstart = 0.0;
	//caminput.Ystart = -500;
	//inner->InitInnerFile("", caminput);
	inner->ReadCamFile(sCam, caminput);//��ȡ�ڷ�λԪ��

	// ģ��
	GeoModelLine *model = new GeoModelLine();
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;
	model->InitModelLine(orbit, attitude, time, inner, modelinput);
	pModel = model;

	////��ȡ���Ƶ�
	//vector<StrGCP> ZY3_GCP;
	//GetGCP(auxpath, ZY3_GCP);

	//// ģ��
	//GeoCalibration *model = new GeoCalibration();
	//StrModelParamInput modelinput;
	//modelinput.isOrbitPoly = false;
	//modelinput.isAttPoly = false;
	//modelinput.timeExtend = 4;
	//model->ExtOrientCali(orbit, attitude, time, inner, modelinput, ZY3_GCP);
	//pModel = model;
}

//////////////////////////////////////////////////////////////////////////
//���ܣ���������֡С����Ӱ����������̬
//���룺��������·����EOP�ļ�·��
//�����С����ָ���̬����ʵ��̬�Ա�
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.15
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::LittleArrayCamera(string auxpath)
{
	//��ȡZY3Sim��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sCam;
	ZY3_01.ZY3SimPATH(auxpath, sAtt, sOrb, sTime, sCam);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadLittleCameraTimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = sEOP;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit, auxpath);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraArray();
	StrCamParamInput caminput;
	caminput.f = 1.7;
	caminput.Xsize = 7. / 1e6;
	caminput.Ysize = 7. / 1e6;
	caminput.Xnum = 1000;
	caminput.Ynum = 1000;
	caminput.Xstart = -500;
	caminput.Ystart = -500;
	inner->InitInnerFile("", caminput);//��ȡ�ڷ�λԪ��

	 // ģ��
	GeoModelArray model;
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = true;
	modelinput.isAttPoly = true;
	modelinput.timeExtend = 4;

	GeoModelRFM rpcModel;
	int m = allTime.size();
	ParseZY3Aux m_File;
	vector<string>filePath;
	m_File.search_directory(auxpath + "\\", "tif", filePath);
	for (int i = 0; i < m; i++)
	{
		model.InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);

		//ƫ�ü���ǰ�в�
		GeoCalibration m_Cali;
		string strTif = filePath[i].substr(0, filePath[i].rfind('.')) + "_";
		//m_Cali.calcGCPerr(&model, strTif, "_before");

		rpcModel.GenRPCFile(&model, 0, 8000, 20, 20, 10);
		string tifPath = filePath[i].substr(0, filePath[i].rfind('.'));
		char rpcPath[512];
		sprintf(rpcPath, "%s_rpc.txt", tifPath.c_str());
		printf("=>Image %d has built RPC\n", i + 1);
		rpcModel.WriteRFMFile(rpcPath);

		//ModelVerify();
		//model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);
		//int step = 10;
		//MatchPoint *gcp = new MatchPoint[1000 / 10 * 1000 / 10];
		//double h = 0, lat, lon;
		//int num = 0;
		//for (int a = 0; a < caminput.Xnum; a += step)
		//{
		//	for (int b = 0; b < caminput.Ynum; b += step)
		//	{
		//		gcp[num].lx = a;			gcp[num].ly = b;
		//		model[0].FromXY2LatLon(gcp[num].lx, gcp[num].ly, h, lat, lon);
		//		model[1].FromLatLon2XY(lat, lon, h, gcp[num].rx, gcp[num].ry);
		//		num++;
		//	}
		//}
		/*	char imgL[512], imgR[512];
		sprintf(imgL, "\\GeoSimulationImage_%d.tif", i + 1);
		sprintf(imgR, "\\GeoSimulationImage_%d.tif", i + 2);
		string strImgL = auxpath + imgL; string strImgR = auxpath + imgR;

		GeoReadImage img1, img2;
		img1.Open(strImgL, GA_ReadOnly);
		img2.Open(strImgR, GA_ReadOnly);
		img1.ReadBlock(0, 0, img1.m_xRasterSize, img1.m_yRasterSize, 0, img1.pBuffer[0]);
		img2.ReadBlock(0, 0, img2.m_xRasterSize, img2.m_yRasterSize, 0, img2.pBuffer[0]);

		double *imgDat1 = new double[1000 * 1000];
		img1.GetDataValueFromBuffer(img1.pBuffer[0], 0, 0, img1.m_xRasterSize, img1.m_yRasterSize, imgDat1);
		GeoHarris m_har;
		vector<MatchPoint> m_pts;
		m_har.Harris(imgDat1, 1000, 1000, 5, 1, 32, 0.8, m_pts);

		int num = m_pts.size();
		MatchPoint *gcp = new MatchPoint[num];
		double h = 0, lat, lon;
		for (int a = 0; a < num; a++)
		{
		gcp[a].lx = m_pts[a].lx;			gcp[a].ly = m_pts[a].ly;
		model[0].FromXY2LatLon(gcp[a].lx, gcp[a].ly, h, lat, lon);
		model[1].FromLatLon2XY(lat, lon, h, gcp[a].rx, gcp[a].ry);
		}

		MatchBasedGeoModel(gcp, num, strImgL, strImgR);
		delete[] gcp; gcp = NULL;*/

	}
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�����ķ���ƥ��
//���룺
//�����
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.17
//////////////////////////////////////////////////////////////////////////
int WorkFlow_ZY3::Image_registration_rpc(string tifPath)
{
	ParseZY3Aux m_File;
	vector<string>filePath;
	m_File.search_directory(tifPath + "\\", "tif", filePath);

	for (int i = 0; i < filePath.size() - 1; i++)
	{
		char exe[512];
		printf("=>Image %d and Image%d begin to register \t", i + 1, i + 2);
		sprintf_s(exe, "%s %s %s 22", "C:\\Users\\wcsgz\\Documents\\2-CProject\\12-�麣����\\x64\\Release\\Register3.3.exe",
			filePath[i].c_str(), filePath[i + 1].c_str());
		system(exe);
		Sleep(100);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//���ܣ����ܵķ���ƥ��
//���룺
//�����
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.16
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::MatchBasedGeoModel(MatchPoint *gcp, int num, string imgL, string imgR)
{
	GeoReadImage img1, img2;
	img1.Open(imgL, GA_ReadOnly);
	img2.Open(imgR, GA_ReadOnly);
	img1.ReadBlock(0, 0, img1.m_xRasterSize, img1.m_yRasterSize, 0, img1.pBuffer[0]);
	img2.ReadBlock(0, 0, img2.m_xRasterSize, img2.m_yRasterSize, 0, img2.pBuffer[0]);

	PhaseCorrelation m_corr;
	CLSMatching m_lsm;
	m_lsm.Init(&img1, &img2);
	string outPath = imgL.substr(0, imgL.rfind('.')) + "_match.pts";
	FILE *fppts = fopen(outPath.c_str(), "w");
	fprintf(fppts, "%s\n", ";");

	for (int i = 0; i < num; i++)
	{
		//if (m_corr.GetPixel(&img1, &img2, gcp[i].lx, gcp[i].ly, gcp[i].rx, gcp[i].ry, 32) == false)
			//continue;
		if (m_lsm.LSMatch(gcp[i].lx, gcp[i].ly, gcp[i].rx, gcp[i].ry, 0.8, true) == false)
			continue;
		double lx = img1.m_yRasterSize - gcp[i].ly;		double ly = img1.m_xRasterSize - gcp[i].lx;
		double rx = img2.m_yRasterSize - gcp[i].ry;		double ry = img2.m_xRasterSize - gcp[i].rx;
		fprintf(fppts, "%.5f\t%.5f\t%.5f\t%.5f\n", lx, ly, rx, ry);
	}
	fclose(fppts);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ���ȡ��ʵ���Ƶ�
//���룺�����ռ�·��
//�������ʵ���Ƶ�match.pts
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.25
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::CalcRealMatchPoint(string workpath)
{
	//��ȡZY3Sim��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sCam;
	ZY3_01.ZY3RealPATH(workpath, sAtt, sOrb, sTime, sCam);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadLittleCameraTimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = sEOP;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	attitude->ReadZY3RealAttFile(allAtt, attitudeinput, orbit, workpath);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraArray();
	StrCamParamInput caminput;
	caminput.f = 1.7;
	caminput.Xsize = 1. / 1e6;
	caminput.Ysize = 1. / 1e6;
	caminput.Xnum = 1000;
	caminput.Ynum = 1000;
	caminput.Xstart = -500;
	caminput.Ystart = -500;
	inner->InitInnerFile("", caminput);//��ȡ�ڷ�λԪ��

	// ģ��
	//GeoModel *model = new GeoModelArray[2];
	GeoModelArray model[2];
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;

	//��ȡDEM
	GeoReadImage DEM;
	//DEM.Open("E:\\0.1\\Point1\\LAC\\7.ƥ��test\\dem.img", GA_ReadOnly);
	DEM.Open("C:\\Users\\wcsgz\\Documents\\5-�������\\���ξ��ȼ�Уv5.0\\ȫ��DEM.tif", GA_ReadOnly);
	DEM.ReadBlock(0, 0, DEM.m_xRasterSize, DEM.m_yRasterSize, 0, DEM.pBuffer[0]);

	ParseZY3Aux m_File;
	vector<string>filePath;
	m_File.search_directory(workpath + "\\", "tif", filePath);
	vector<Attitude>attMeas, attModify, attRelative;
	OffsetAngle Ru;
	vector<strRMS>accuracy1, accuracy2;

	for (int i = 0; i < allTime.size() - 1; i++)
	{
		model[0].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);
		model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);

		vector<MatchPoint>pGCP;	MatchPoint pGCPtmp;
		double line, sample, rline, rsample, H = 0, Lat, Lon;
		for (line = 700; line < 1000; )
		{
			for (sample = 10; sample < 1000;)
			{
				model[0].FromXY2LatLon(line, sample, H, Lat, Lon);
				int j = 0;
				while (1)
				{
					double HH = DEM.GetDataValue(Lon / PI * 180, Lat / PI * 180, -99999, 0, 0);
					if (abs(HH - H) > 1e-4&&j++ < 30)
					{
						H = HH;
						model[0].FromXY2LatLon(line, sample, H, Lat, Lon);
					}
					else
					{
						break;
					}
				}
				if (fabs(H + 99999.) < 1.e-6)
					continue;

				model[1].FromLatLon2XY(Lat, Lon, H, rline, rsample);
				if (rline>0&& rline<1000&&rsample>0&&rsample<1000)
				{
					pGCPtmp.lx = line; pGCPtmp.ly = sample;
					pGCPtmp.rx = rline; pGCPtmp.ry = rsample+0.1;
					pGCP.push_back(pGCPtmp);
				}

				sample += 10;
			}
			line += 10;
		}

		printf("=>Image %d's GCP has calculated\n", i + 1);
		string output = filePath[i].substr(0, filePath[i].rfind('.')) + "_match.pts";
		FILE *fp = fopen(output.c_str(), "w");
		fprintf(fp, "; %d\n", pGCP.size());
		for (int i = 0; i < pGCP.size(); i++)
		{
			fprintf(fp, "%f\t%f\t%f\t%f\n", pGCP[i].ly, pGCP[i].lx, pGCP[i].ry, pGCP[i].rx);
		}
		fclose(fp);
	}
	DEM.Destroy();
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�����ָ�����̬
//���룺�����ռ�·��
//������ָ�����̬
//ע�⣺�������У
//���ߣ�GZC
//���ڣ�2017.08.17
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::CalcRealAttitude(string workpath)
{
	//��ȡZY3Sim��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sCam;
	ZY3_01.ZY3SimPATH(workpath, sAtt, sOrb, sTime, sCam);
	//ZY3_01.ZY3RealPATH(workpath, sAtt, sOrb, sTime, sCam);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadLittleCameraTimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = sEOP;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	//attitude->ReadZY3RealAttFile(allAtt, attitudeinput, orbit, workpath);
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit, workpath);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraArray();
	StrCamParamInput caminput;
	caminput.f = 1.7;
	caminput.Xsize = 1. / 1e6;
	caminput.Ysize = 1. / 1e6;
	caminput.Xnum = 1000;
	caminput.Ynum = 1000;
	caminput.Xstart = -500;
	caminput.Ystart = -500;
	inner->InitInnerFile("", caminput);//��ȡ�ڷ�λԪ��

	// ģ��
	//GeoModel *model = new GeoModelArray[2];
	GeoModelArray model[2];
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;

	//��ȡDEM
	GeoReadImage DEM;
	//DEM.Open("E:\\0.1\\Point1\\LAC\\7.ƥ��test\\dem.img", GA_ReadOnly);
	DEM.Open("C:\\Users\\wcsgz\\Documents\\5-�������\\���ξ��ȼ�Уv5.0\\ȫ��DEM.tif", GA_ReadOnly);
	DEM.ReadBlock(0, 0, DEM.m_xRasterSize, DEM.m_yRasterSize, 0, DEM.pBuffer[0]);

	ParseZY3Aux m_File;
	vector<string>filePath;
	m_File.search_directory(workpath + "\\", "pts", filePath);
	vector<Attitude>attMeas, attModify, attRelative;
	OffsetAngle Ru;	vector<OffsetAngle>RuForward, RuBackward;
	vector<strRMS>accuracy1, accuracy2;
	//���������̬
	for (int i = 0; i < allTime.size() - 1; i++)
	{
		model[0].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);
		if (i == 0)
		{
			attMeas.push_back(model[0].GetQuatCam2wgs84());
			attModify.push_back(model[0].GetQuatCam2wgs84());
		}
		else
		{
			attMeas.push_back(model[0].GetQuatCam2wgs84());
			model[0].updateOffsetmatrix(Ru);
			attModify.push_back(model[0].GetQuatCam2wgs84());
		}
		model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);

		FILE *fp = fopen(filePath[i].c_str(), "r");
		int num;
		fscanf(fp, "%*s %d", &num);
		double lx, ly, rx, ry, H = 0, Lat, Lon;
		StrGCP *pGCP = new StrGCP[num];
		int numGCP = 0;
		for (int k = 0; k < num; k++)
		{
			//��ȡƥ�����������꣬ע��xΪ�ع����꣬yΪ��������
			fscanf(fp, "%lf\t%lf\t%lf\t%lf\n", &ly, &lx, &ry, &rx);
			model[0].FromXY2LatLon(lx, ly, H, Lat, Lon);
			//���DEM����Ӱ��1���(x1,y1)��Ӧ�������(Lon,Lat,H);
			int j = 0;
			while (1)
			{
				double HH = DEM.GetDataValue(Lon / PI * 180, Lat / PI * 180, -99999, 0, 0);
				if (abs(HH - H) > 1e-4&&j++ < 30)
				{
					H = HH;
					model[0].FromXY2LatLon(lx, ly, H, Lat, Lon);
				}
				else
				{
					break;
				}
			}
			if (fabs(H + 99999.) < 1.e-6)
				continue;
			pGCP[k].x = rx; pGCP[k].y = ry;
			pGCP[k].h = H; pGCP[k].lat = Lat; pGCP[k].lon = Lon;
			numGCP++;
		}
		fclose(fp);

		//ƫ�ü���ǰ�в�
		GeoCalibration m_Cali;
		m_Cali.calcGCPerr(model + 1, filePath[i], "_before", accuracy1,1);
		//m_Cali.calcRMS(model + 1, workpath + "\\before_ru.txt", pGCP, numGCP);

		printf("=>Modify quaternion %d Now\n", i + 1);
		m_Cali.calcOffsetMatrix(model + 1, pGCP, numGCP, Ru);
		RuForward.push_back(Ru);

		//ƫ�ü����в�
		//model[1].updateOffsetmatrix(Ru);
		//m_Cali.calcGCPerr(model + 1, filePath[i], "_after", accuracy2,1);
		//m_Cali.calcRMS(model + 1, workpath + "\\after_ru.txt" , pGCP, numGCP);

		delete[]pGCP; pGCP = NULL;
	}

	//���������̬
	for (int i = allTime.size() - 2; i >=0; i--)
	{
		model[0].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);//У��֡
		model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);//��׼֡
		if (i == allTime.size() - 2)
		{
			attMeas.push_back(model[1].GetQuatCam2wgs84());
			attModify.push_back(model[1].GetQuatCam2wgs84());
		}
		else
		{
			attMeas.push_back(model[1].GetQuatCam2wgs84());
			model[1].updateOffsetmatrix(Ru);
			attModify.push_back(model[1].GetQuatCam2wgs84());
		}

		FILE *fp = fopen(filePath[i].c_str(), "r");
		int num;
		fscanf(fp, "%*s %d", &num);
		double lx, ly, rx, ry, H = 0, Lat, Lon;
		StrGCP *pGCP = new StrGCP[num];
		int numGCP = 0;
		for (int k = 0; k < num; k++)
		{
			//��ȡƥ�����������꣬ע��xΪ�ع����꣬yΪ��������
			fscanf(fp, "%lf\t%lf\t%lf\t%lf\n", &ly, &lx, &ry, &rx);
			model[1].FromXY2LatLon(rx, ry, H, Lat, Lon);
			//���DEM����Ӱ��1���(x1,y1)��Ӧ�������(Lon,Lat,H);
			int j = 0;
			while (1)
			{
				double HH = DEM.GetDataValue(Lon / PI * 180, Lat / PI * 180, -99999, 0, 0);
				if (abs(HH - H) > 1e-4&&j++ < 30)
				{
					H = HH;
					model[1].FromXY2LatLon(rx, ry, H, Lat, Lon);
				}
				else
				{
					break;
				}
			}
			if (fabs(H + 99999.) < 1.e-6)
				continue;
			model[0].FromLatLon2XY(Lat, Lon,H, rx, ry);
			pGCP[k].x = lx; pGCP[k].y = ly;
			pGCP[k].h = H; pGCP[k].lat = Lat; pGCP[k].lon = Lon;
			numGCP++;
		}
		fclose(fp);

		//ƫ�ü���ǰ�в�
		GeoCalibration m_Cali;
		//m_Cali.calcGCPerr(model, filePath[i], "_before", accuracy1,0);
		//m_Cali.calcRMS(model + 1, workpath + "\\before_ru.txt", pGCP, numGCP);

		printf("=>Modify quaternion %d Now\n", i + 1);
		m_Cali.calcOffsetMatrix(model, pGCP, numGCP, Ru);
		RuBackward.insert(RuBackward.begin(),Ru);

		//ƫ�ü����в�
		//model[0].updateOffsetmatrix(Ru);
		//m_Cali.calcGCPerr(model, filePath[i], "_after", accuracy2,0);
		//m_Cali.calcRMS(model + 1, workpath + "\\after_ru.txt" , pGCP, numGCP);

		delete[]pGCP; pGCP = NULL;
	}

	//RuFusion(RuForward, RuBackward);
	for (int i=0;i<RuForward.size();i++)
	{
		//model[0].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);
		model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i+1].lineTimeUT);
		Ru = (RuForward[i] + RuForward[i])/2.0;
		model[1].updateOffsetmatrix(Ru);
		GeoCalibration m_Cali;
		m_Cali.calcGCPerr(model+1, filePath[i], "_after", accuracy2, 1);
	}
	
	OutputRMS(workpath, accuracy1, accuracy2);

	DEM.Destroy();
	//CompareMeasModifyAndReal(attMeas, attModify, workpath);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ��ں�ǰ��ͺ���ƫ�þ���Ru
//���룺ǰ��Ru����ֵRuForward������Ru����ֵRuBackward
//�����Ru�м�ֵRuForward
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.25
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::RuFusion(vector<OffsetAngle>&RuForward, vector<OffsetAngle>RuBackward)
{
	vector<OffsetAngle>Ru;
	OffsetAngle RuTmp;
	double R1[9], R2[9],R3[9];
	for (int i=0;i<RuForward.size();i++)
	{
		m_base.rot(RuForward[i].RuPhi, RuForward[i].RuOmega, RuForward[i].RuKappa, R1);
		m_base.rot(RuBackward[i].RuPhi, RuBackward[i].RuOmega, RuBackward[i].RuKappa, R2);
		m_base.invers_matrix(R2, 3);
		m_base.Multi(R1, R2, R3, 3, 3, 3);
		m_base.Matrix2Eulor(R3, 213, RuTmp.RuPhi, RuTmp.RuOmega, RuTmp.RuKappa);
		Ru.push_back(RuTmp / 2.);
	}
	RuForward.clear();
	RuForward.assign(Ru.begin(), Ru.end());
}
//////////////////////////////////////////////////////////////////////////
//���ܣ��Ƚϻָ�����̬
//���룺������̬��������̬����ʵ��̬
//������ȽϽ��txt
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.20
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::CompareMeasModifyAndReal(vector<Attitude>Meas, vector<Attitude>Modify, string realAttPath)
{
	ParseZY3Aux m_parse;
	vector<Attitude>realAtt, attRelat1, attRelat2;
	realAttPath += "\\ATT.txt";
	m_parse.ReadZY301AttTXT(realAttPath, realAtt);
	GeoAttitude_ZY3 m_Att;
	m_Att.TransZY3AttFile(realAtt, sEOP);

	for (int i = 0; i < Meas.size(); i++)
	{
		Attitude realAttInter;
		m_base.QuatInterpolation(realAtt, Meas[i].UTC, realAttInter);
		double qL[4], qR[4], dq[4];
		qL[0] = -Meas[i].Q0, qL[1] = Meas[i].Q1, qL[2] = Meas[i].Q2, qL[3] = Meas[i].Q3;
		qR[0] = realAttInter.Q0, qR[1] = realAttInter.Q1, qR[2] = realAttInter.Q2, qR[3] = realAttInter.Q3;
		m_base.quatMult(qR, qL, dq);
		Attitude tmp;
		tmp.Q1 = dq[1] * 2 / PI * 180 * 3600;
		tmp.Q2 = dq[2] * 2 / PI * 180 * 3600;
		tmp.Q3 = dq[3] * 2 / PI * 180 * 3600;
		attRelat1.push_back(tmp);

		qL[0] = Modify[i].Q0, qL[1] = Modify[i].Q1, qL[2] = Modify[i].Q2, qL[3] = Modify[i].Q3;
		qR[0] = -realAttInter.Q0, qR[1] = realAttInter.Q1, qR[2] = realAttInter.Q2, qR[3] = realAttInter.Q3;
		m_base.quatMult(qR, qL, dq);
		tmp.Q1 = dq[1] * 2 / PI * 180 * 3600;
		tmp.Q2 = dq[2] * 2 / PI * 180 * 3600;
		tmp.Q3 = dq[3] * 2 / PI * 180 * 3600;
		attRelat2.push_back(tmp);
	}

	string strRu = realAttPath.substr(0, realAttPath.rfind('\\') + 1) + "CompareAtt.txt";
	FILE *fprelative = fopen(strRu.c_str(), "w");
	for (int i = 0; i < Meas.size(); i++)
	{
		fprintf(fprelative, "%.6f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\t%.9f\n", Meas[i].UTC, attRelat1[i].Q1,
			attRelat1[i].Q2, attRelat1[i].Q3, attRelat2[i].Q1, attRelat2[i].Q2, attRelat2[i].Q3);
	}
	fclose(fprelative);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�������ݿ��Ƶ����Ĳв�
//���룺����vector<RMS>accuracy
//���������仯
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.23
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::OutputRMS(string outFile, vector<strRMS>accuracy1, vector<strRMS>accuracy2)
{
	string strOut = outFile + "\\CompareRMS.txt";
	FILE *fp = fopen(strOut.c_str(), "w");
	fprintf(fp, "rmsx\t rmsy\t Plane\t rmsx\t rmsy\t Plane\n");
	for (int i = 0; i < accuracy1.size(); i++)
	{
		fprintf(fp, "%.6f\t%.6f\t%.6f\t%.6f\t%.6f\t%.6f\n", accuracy1[i].rmsx, accuracy1[i].rmsy, accuracy1[i].rmsall,
			accuracy2[i].rmsx, accuracy2[i].rmsy, accuracy2[i].rmsall);
	}
	fclose(fp);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�����ƥ�������ٶȣ�Ȼ���ϲ�����̬���������˲�
//���룺�����ռ�Ŀ¼
//��������Ƶ㾫�ȱȽ�
//ע�⣺
//���ߣ�GZC
//���ڣ�2017.08.30
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::CalcOmegaKalman(string workpath)
{
	//��ȡZY3Sim��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sCam;
	ZY3_01.ZY3SimPATH(workpath, sAtt, sOrb, sTime, sCam);
	//ZY3_01.ZY3RealPATH(workpath, sAtt, sOrb, sTime, sCam);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadLittleCameraTimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = sEOP;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	//attitude->ReadZY3RealAttFile(allAtt, attitudeinput, orbit, workpath);
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit, workpath);

	//��ȡEOP
	int num;
	FILE *fp = fopen((workpath + "\\WGS84ToJ2000_Error.txt").c_str(), "r");
	fscanf(fp, "%d\n", &num);
	structEOP *strEOP = new structEOP[num];
	for (int i=0;i<num;i++)
	{
		fscanf(fp, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", &strEOP[i].R[0], 
			&strEOP[i].R[1], &strEOP[i].R[2], &strEOP[i].R[3], &strEOP[i].R[4],
			&strEOP[i].R[5], &strEOP[i].R[6], &strEOP[i].R[7], &strEOP[i].R[8]);// WGS84ToJ2000
	}

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraArray();
	StrCamParamInput caminput;
	caminput.f = 1.7;
	caminput.Xsize = 1. / 1e6;
	caminput.Ysize = 1. / 1e6;
	caminput.Xnum = 1000;
	caminput.Ynum = 1000;
	caminput.Xstart = -500;
	caminput.Ystart = -500;
	inner->InitInnerFile("", caminput);//��ȡ�ڷ�λԪ��

	// ģ��
	//GeoModel *model = new GeoModelArray[2];
	GeoModelArray model[2];
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;

	//��ȡDEM
	GeoReadImage DEM;
	//DEM.Open("E:\\0.1\\Point1\\LAC\\7.ƥ��test\\dem.img", GA_ReadOnly);
	DEM.Open("C:\\Users\\wcsgz\\Documents\\5-�������\\���ξ��ȼ�Уv5.0\\ȫ��DEM.tif", GA_ReadOnly);
	DEM.ReadBlock(0, 0, DEM.m_xRasterSize, DEM.m_yRasterSize, 0, DEM.pBuffer[0]);

	ParseZY3Aux m_File;
	vector<string>filePath;
	m_File.search_directory(workpath + "\\", "pts", filePath);
	vector<Attitude>attMeas, attModify, attRelative;
	OffsetAngle Ru;	vector<OffsetAngle>RuForward, RuBackward;
	vector<strRMS>accuracy1, accuracy2;
	vector<Gyro>omega;

	//���������̬
	for (int i = 0; i < allTime.size() - 1; i++)
	{
		model[0].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);
		model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);
		attMeas.push_back(model[0].GetQuatCam2wgs84());

		FILE *fp = fopen(filePath[i].c_str(), "r");
		int num;
		fscanf(fp, "%*s %d", &num);
		double lx, ly, rx, ry, H = 0, Lat, Lon;
		StrGCP *pGCP = new StrGCP[num];
		int numGCP = 0;
		for (int k = 0; k < num; k++)
		{
			//��ȡƥ�����������꣬ע��xΪ�ع����꣬yΪ��������
			fscanf(fp, "%lf\t%lf\t%lf\t%lf\n", &ly, &lx, &ry, &rx);
			model[0].FromXY2LatLon(lx, ly, H, Lat, Lon);
			//���DEM����Ӱ��1���(x1,y1)��Ӧ�������(Lon,Lat,H);
			int j = 0;
			while (1)
			{
				double HH = DEM.GetDataValue(Lon / PI * 180, Lat / PI * 180, -99999, 0, 0);
				if (abs(HH - H) > 1e-4&&j++ < 30)
				{
					H = HH;
					model[0].FromXY2LatLon(lx, ly, H, Lat, Lon);
				}
				else
				{
					break;
				}
			}
			if (fabs(H + 99999.) < 1.e-6)
				continue;
			pGCP[k].x = rx; pGCP[k].y = ry;
			pGCP[k].h = H; pGCP[k].lat = Lat; pGCP[k].lon = Lon;
			numGCP++;
		}
		fclose(fp);

		//ƫ�ü���ǰ�в�
		GeoCalibration m_Cali;
		m_Cali.calcGCPerr(model + 1, filePath[i], "_before", accuracy1, 1);

		printf("=>calculate omega of image %d \n", i + 1);
		m_Cali.calcOffsetMatrix(model + 1, pGCP, numGCP, Ru);
		RuForward.push_back(Ru);

		Gyro omTmp;
		m_Cali.CalcRealOmega(model, Ru, &strEOP[i], omTmp);
		omega.push_back(omTmp);

		delete[]pGCP; pGCP = NULL;
	}

	AttDeter attDet;
	attDet.ExtendedKalmanFilter(attMeas,omega);
	attitude->upDateAtt(attMeas, attitudeinput);

	for (int i = 0; i < attMeas.size(); i++)
	{
		model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i+1].lineTimeUT);
		GeoCalibration m_Cali;
		m_Cali.calcGCPerr(model+1, filePath[i], "_after", accuracy2, 1);
	}

	OutputRMS(workpath, accuracy1, accuracy2);

	DEM.Destroy();
	//CompareMeasModifyAndReal(attMeas, attModify, workpath);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�ͨ��ϡ����������̬
//���룺�����ռ�·��
//������ָ�����̬
//ע�⣺����ϡ�����ʽ
//���ߣ�GZC
//���ڣ�2017.09.04
//////////////////////////////////////////////////////////////////////////
void WorkFlow_ZY3::CalcRealAttitude_sparse(string workpath)
{
	//��ȡZY3Sim��������
	ParseZY3Aux ZY3_01;
	vector<Orbit_Ep> allEp;
	vector<Attitude> allAtt;
	vector<LineScanTime> allTime;
	string sOrb, sAtt, sTime, sCam;
	ZY3_01.ZY3SimPATH(workpath, sAtt, sOrb, sTime, sCam);
	//ZY3_01.ZY3RealPATH(workpath, sAtt, sOrb, sTime, sCam);
	ZY3_01.ReadZY301OrbTXT(sOrb, allEp);
	ZY3_01.ReadZY301AttTXT(sAtt, allAtt);
	ZY3_01.ReadLittleCameraTimeTXT(sTime, allTime);

	// ���
	GeoOrbit *orbit = new GeoOrbitEarth_ZY3();
	StrOrbitParamInput orbitinput;
	orbitinput.DatumName = "WGS84";
	orbitinput.m_EOP = sEOP;
	orbitinput.m_JPL = "";
	orbitinput.m_PolyOrder = 3;
	orbit->ReadZY3EphFile(allEp, orbitinput);

	// ��̬
	GeoAttitude *attitude = new GeoAttitude_ZY3();
	StrAttParamInput attitudeinput;
	attitudeinput.DatumName = "WGS84";
	attitudeinput.m_PolyOrder = 2;
	//attitude->ReadZY3RealAttFile(allAtt, attitudeinput, orbit, workpath);
	attitude->ReadZY3AttFile(allAtt, attitudeinput, orbit, workpath);

	// ʱ��
	GeoTime *time = new GeoTime_ZY3();
	time->ReadZY3TimeFile(allTime);

	// ���
	GeoCamera *inner = new GeoCameraArray();
	StrCamParamInput caminput;
	caminput.f = 1.7;
	caminput.Xsize = 1. / 1e6;
	caminput.Ysize = 1. / 1e6;
	caminput.Xnum = 1000;
	caminput.Ynum = 1000;
	caminput.Xstart = -500;
	caminput.Ystart = -500;
	inner->InitInnerFile("", caminput);//��ȡ�ڷ�λԪ��

	// ģ��
	//GeoModel *model = new GeoModelArray[2];
	GeoModelArray *model = new GeoModelArray[allTime.size()];
	//GeoModelArray model[2];
	StrModelParamInput modelinput;
	modelinput.isOrbitPoly = false;
	modelinput.isAttPoly = false;
	modelinput.timeExtend = 4;
	string strDEM = "C:\\Users\\wcsgz\\Documents\\5-�������\\���ξ��ȼ�Уv5.0\\ȫ��DEM.tif";
	

	//��ȡDEM
	GeoReadImage DEM;
	DEM.Open("C:\\Users\\wcsgz\\Documents\\5-�������\\���ξ��ȼ�Уv5.0\\ȫ��DEM.tif", GA_ReadOnly);
	DEM.ReadBlock(0, 0, DEM.m_xRasterSize, DEM.m_yRasterSize, 0, DEM.pBuffer[0]);

	ParseZY3Aux m_File;
	vector<string>filePath;
	m_File.search_directory(workpath + "\\", "pts", filePath);
	OffsetAngle Ru;	vector<OffsetAngle>RuForward, RuBackward;
	vector<strRMS>accuracy1, accuracy2;

	int nMatch = 0;//��������ƥ��������
	for (int i = 0; i < allTime.size() - 1; i++)
	{
		FILE *fp = fopen(filePath[i].c_str(), "r");
		int num;
		fscanf(fp, "%*s %d", &num);
		nMatch += num;
		fclose(fp);
	}

	conjugatePoints *pMatchs = new conjugatePoints[nMatch];
	nMatch = 0;
	for (int i = 0; i < allTime.size() - 1; i++)
	{
		model[i].SetDEMpath(strDEM); model[i+1].SetDEMpath(strDEM);
		model[i].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);
		model[i+1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);

		FILE *fp = fopen(filePath[i].c_str(), "r");
		int num;
		fscanf(fp, "%*s %d", &num);
		double lx, ly, rx, ry, H = 0, Lat, Lon;
		StrGCP *pGCP = new StrGCP[num];
		int numGCP = 0;
		for (int k = 0; k < num; k++)
		{
			//��ȡƥ�����������꣬ע��xΪ�ع����꣬yΪ��������
			fscanf(fp, "%lf\t%lf\t%lf\t%lf\n", &ly, &lx, &ry, &rx);
			pMatchs[nMatch].xl = lx; pMatchs[nMatch].yl = ly;
			pMatchs[nMatch].xr = rx; pMatchs[nMatch].yr = ry;
			pMatchs[nMatch].nIndex[0] = i;
			pMatchs[nMatch].nIndex[1] = i+1;
			/*H = model[i].CalcHeihtFromDEM(lx, ly, Lat, Lon);*/
			model[i].FromXY2LatLon(lx, ly, H, Lat, Lon);
			//���DEM����Ӱ��1���(x1,y1)��Ӧ�������(Lon,Lat,H);
			int j = 0;
			while (1)
			{
				double HH = DEM.GetDataValue(Lon / PI * 180, Lat / PI * 180, -99999, 0, 0);
				if (abs(HH - H) > 1e-4&&j++ < 30)
				{
					H = HH;
					model[i].FromXY2LatLon(lx, ly, H, Lat, Lon);
				}
				else
				{
					break;
				}
			}
			if (fabs(H + 99999.) < 1.e-6)
				continue;
			pGCP[k].x = rx; pGCP[k].y = ry;
			pGCP[k].h = H; pGCP[k].lat = Lat; pGCP[k].lon = Lon;
			nMatch++;
			numGCP++;
		}
		fclose(fp);

		//ƫ�ü���ǰ�в�
		GeoCalibration m_Cali;
		//m_Cali.calcGCPerr(model + 1, filePath[i], "_before", accuracy1, 1);

		printf("=>Modify quaternion %d Now\n", i + 1);
		m_Cali.calcOffsetMatrix(&model[i+1], pGCP, numGCP, Ru);
		model[i + 1].updateOffsetmatrix(Ru);

		delete[]pGCP; pGCP = NULL;
	}
	double *pDis = NULL;
	autoGeoCalibration_sparse(model, allTime.size(), pMatchs, nMatch, 1, 1, pDis, workpath);

	//RuFusion(RuForward, RuBackward);
	//for (int i = 0; i < RuForward.size(); i++)
	//{
	//	//model[0].InitModelArray(orbit, attitude, inner, modelinput, allTime[i].lineTimeUT);
	//	model[1].InitModelArray(orbit, attitude, inner, modelinput, allTime[i + 1].lineTimeUT);
	//	Ru = (RuForward[i] + RuForward[i]) / 2.0;
	//	model[1].updateOffsetmatrix(Ru);
	//	GeoCalibration m_Cali;
	//	m_Cali.calcGCPerr(model + 1, filePath[i], "_after", accuracy2, 1);
	//}

	//OutputRMS(workpath, accuracy1, accuracy2);

	DEM.Destroy();
	//CompareMeasModifyAndReal(attMeas, attModify, workpath);
}

//////////////////////////////////////////////////////////////////////////
//���ܣ�ϡ��������
//���룺�����ռ�·��
//�����
//ע�⣺
//���ߣ�JYH
//���ڣ�2017.09.04
//////////////////////////////////////////////////////////////////////////
bool WorkFlow_ZY3::autoGeoCalibration_sparse(GeoModelArray *pGeoModel, int num, 
	conjugatePoints* pMatch, int nMatch, int xOrder, int yOrder, double *&pRes, string sRes)
{
	if (num < 2)
	{
		printf("=>need at least two images!\n");
		return false;
	}
	//��ȡDEM
	GeoReadImage DEM;
	DEM.Open("C:\\Users\\wcsgz\\Documents\\5-�������\\���ξ��ȼ�Уv5.0\\ȫ��DEM.tif", GA_ReadOnly);
	DEM.ReadBlock(0, 0, DEM.m_xRasterSize, DEM.m_yRasterSize, 0, DEM.pBuffer[0]);

	double a = 6378137, b = 6356752.314;//�������

	int alongOrder = xOrder;
	int acrossOrder = yOrder;

	int nUnknown1 = (alongOrder + 2) + (acrossOrder + 2);
	int nHalfUnknown1 = alongOrder + 2;
	int nUnknown2 = nMatch * 2;
	int nUnknown = nUnknown1 + nUnknown2;

	double *pUnknown = new double[nUnknown];
	memset(pUnknown, 0, sizeof(double)*nUnknown);

	int wi, hi;
	wi = pGeoModel[0].get_m_width();
	hi = pGeoModel[0].get_m_height();
	double camx0, camy0, camx1, camy1;
	pGeoModel[0].GetInner(0, 0, camx0, camy0);
	pGeoModel[0].GetInner(wi - 1, hi - 1, camx1, camy1);
	pUnknown[0] = camx0;
	pUnknown[alongOrder + 1] = (camx1 - camx0);///(hi-1);
	pUnknown[nHalfUnknown1] = camy0;
	pUnknown[nHalfUnknown1 + 1] = (camy1 - camy0);///(wi-1);

	//��ȡ��ֵ������̣߳��������ٸ��ĸ߳�;
	double lat1, lon1, h1, lat2, lon2, h2;
	double *pH = new double[nMatch];
	for (int i = 0; i < nMatch; i++)
	{
		pGeoModel[pMatch[i].nIndex[0]].FromXY2LatLon(pMatch[i].xl, pMatch[i].yl, h1, lat1, lon1);
		//���DEM����Ӱ��1���(x1,y1)��Ӧ�������(Lon,Lat,H);
		int j = 0;
		while (1)
		{
			double HH = DEM.GetDataValue(lon1 / PI * 180, lat1 / PI * 180, -99999, 0, 0);
			if (abs(HH - h1) > 1e-4&&j++ < 30)
			{
				h1 = HH;
				pGeoModel[pMatch[i].nIndex[0]].FromXY2LatLon(pMatch[i].xl, pMatch[i].yl, h1, lat1, lon1);
			}
			else
			{
				break;
			}
		}
		//h1 = pGeoModel[pMatch[i].nIndex[0]].CalcHeihtFromDEM(pMatch[i].xl, pMatch[i].yl, lat1, lon1);
		if (fabs(h1 + 99999.) < 1.e-6)
			h1 = 0;
		h2 = h1;
		pGeoModel[pMatch[i].nIndex[1]].FromXY2LatLon(pMatch[i].xr, pMatch[i].yr, h2, lat2, lon2);
		//���DEM����Ӱ��1���(x1,y1)��Ӧ�������(Lon,Lat,H);
		j = 0;
		while (1)
		{
			double HH = DEM.GetDataValue(lon2 / PI * 180, lat2 / PI * 180, -99999, 0, 0);
			if (abs(HH - h2) > 1e-4&&j++ < 30)
			{
				h2 = HH;
				pGeoModel[pMatch[i].nIndex[1]].FromXY2LatLon(pMatch[i].xr, pMatch[i].yr, h2, lat2, lon2);
			}
			else
			{
				break;
			}
		}
		//h2 = pGeoModel[pMatch[i].nIndex[1]].CalcHeihtFromDEM(pMatch[i].xr, pMatch[i].yr, lat2, lon2);
		if (fabs(h2 + 99999.) < 1.e-6)
			h2 = 0;

		pH[i] = (h1 + h2) / 2.;

		double tmpX1, tmpY1, tmpZ1, tmpX2, tmpY2, tmpZ2;
		pGeoModel[pMatch[i].nIndex[0]].Fromxyh2XYZ(pMatch[i].xl, pMatch[i].yl, h1, tmpX1, tmpY1, tmpZ1);
		pGeoModel[pMatch[i].nIndex[1]].Fromxyh2XYZ(pMatch[i].xr, pMatch[i].yr, h2, tmpX2, tmpY2, tmpZ2);
		//geograph2rect(lat1 / 180.*PI, -lon1 / 180.*PI, h1, WGS84, &tmpX1, &tmpY1, &tmpZ1);
		//geograph2rect(lat2 / 180.*PI, -lon2 / 180.*PI, h2, WGS84, &tmpX2, &tmpY2, &tmpZ2);

		//		double tZ = tmpZ1/fabs(tmpZ1)*sqrt((b+h1)*(b+h1)-(b+h1)*(b+h1)/((a+h1)*(a+h1))*(tmpX1*tmpX1+tmpY1*tmpY1));

		pMatch[i].X = pUnknown[nUnknown1 + 2 * i] = (tmpX1 + tmpX2) / 2.;
		pMatch[i].Y = pUnknown[nUnknown1 + 2 * i + 1] = (tmpY1 + tmpY2) / 2.;
		pMatch[i].Z = (tmpZ1 + tmpZ2) / 2.;
	}

	typedef Triplet<double> T;
	std::vector<T> tripletList;//ϡ������Ԫ��  
	VectorXd eigL(4 * nMatch);
	double R[9], XYZs[3]; //�洢��̬���������λ��;

	int nIter = 0;

	do
	{
		tripletList.clear();
		for (int i = 0; i < nMatch; i++)
		{
			double X, Y, Z, XX, YY, ZZ;
			X = pUnknown[nUnknown1 + 2 * i];
			Y = pUnknown[nUnknown1 + 2 * i + 1];

			double mulpParam;

			if (pMatch[i].Z < 0)
				mulpParam = -1.;
			else
				mulpParam = 1.;

			Z = mulpParam*sqrt((b + pH[i])*(b + pH[i]) - (b + pH[i])*(b + pH[i]) / ((a + pH[i])*(a + pH[i]))*(X*X + Y*Y));
			//x,y
			//fx;
			//			memset(pParams,0,sizeof(double)*nUnknown);

			double phiX = 0, phiY = 0;
			//phix = a0+a1*x+a2*x*x+a3*x*x*x+b1*y;
			//phiy = a0+a1*x+a2*x*x+a3*x*x*x+b1*y;
			for (int nx = 0; nx <= alongOrder; nx++)
			{
				double value = pow(pMatch[i].xl / (wi - 1), nx);
				tripletList.push_back(T(4 * i, nx, -value));
				phiX += pUnknown[nx] * value;
			}
			tripletList.push_back(T(4 * i, alongOrder + 1, -pMatch[i].yl / (hi - 1)));
			phiX += pUnknown[alongOrder + 1] * pMatch[i].yl / (hi - 1);

			for (int nx = 0; nx <= acrossOrder; nx++)
			{
				double value = pow(pMatch[i].xl / (wi - 1), nx);
				tripletList.push_back(T(4 * i + 1, nHalfUnknown1 + nx, -value));
				phiY += pUnknown[nHalfUnknown1 + nx] * value;
			}
			tripletList.push_back(T(4 * i + 1, nHalfUnknown1 + acrossOrder + 1, -pMatch[i].yl / (hi - 1)));
			phiY += pUnknown[nHalfUnknown1 + acrossOrder + 1] * pMatch[i].yl / (hi - 1);

			//double testPhix,testPhiy;
			//pGeoModel[pMatch[i].nIndex[0]].getSensorInfor().getCoorInCamera(pMatch[i].xl,pMatch[i].yl,testPhix,testPhiy,0);

			pGeoModel[pMatch[i].nIndex[0]].GetCam2WGS84(R);
			double ep[3];
			pGeoModel[pMatch[i].nIndex[0]].GetCamPos(ep);
			XYZs[0] = ep[0], XYZs[1] = ep[1], XYZs[2] = ep[2];
			//pGeoModel[pMatch[i].nIndex[0]].getExtOrientationWithRu(pMatch[i].xl,pMatch[i].yl,XYZs,R,-1);
			XX = R[0] * (X - XYZs[0]) + R[3] * (Y - XYZs[1]) + R[6] * (Z - XYZs[2]);
			YY = R[1] * (X - XYZs[0]) + R[4] * (Y - XYZs[1]) + R[7] * (Z - XYZs[2]);
			ZZ = R[2] * (X - XYZs[0]) + R[5] * (Y - XYZs[1]) + R[8] * (Z - XYZs[2]);

			double div_Z_X = -mulpParam*(b + pH[i])*(b + pH[i]) / ((a + pH[i])*(a + pH[i])) /
				sqrt((b + pH[i])*(b + pH[i]) - (b + pH[i])*(b + pH[i]) / ((a + pH[i])*(a + pH[i]))*(X*X + Y*Y))*X;

			double div_Z_Y = -mulpParam*(b + pH[i])*(b + pH[i]) / ((a + pH[i])*(a + pH[i])) /
				sqrt((b + pH[i])*(b + pH[i]) - (b + pH[i])*(b + pH[i]) / ((a + pH[i])*(a + pH[i]))*(X*X + Y*Y))*Y;

			tripletList.push_back(T(4 * i, nUnknown1 + 2 * i, ((R[0] + R[6] * div_Z_X)*ZZ - (R[2] + R[8] * div_Z_X)*XX) / ZZ / ZZ));
			tripletList.push_back(T(4 * i, nUnknown1 + 2 * i + 1, ((R[3] + R[6] * div_Z_Y)*ZZ - (R[5] + R[8] * div_Z_Y)*XX) / ZZ / ZZ));

			double L = phiX - XX / ZZ;
			eigL[4 * i] = L;

			//fy
			//			memset(pParams,0,sizeof(double)*nUnknown);

			//for (int n = 0;n<nAcrossOrder+1;n++)
			//{
			//	//pParams[ccdid*(nAlongOrder+nAcrossOrder+2)+nAlongOrder+1+n] = -pow(s,n);
			//	tripletList.push_back(T(4*i+1,ccdid*(nAlongOrder+nAcrossOrder+2)+nAlongOrder+1+n,-pow(s,n)));
			//}

			tripletList.push_back(T(4 * i + 1, nUnknown1 + 2 * i, ((R[1] + R[7] * div_Z_X)*ZZ - (R[2] + R[8] * div_Z_X)*YY) / ZZ / ZZ));
			tripletList.push_back(T(4 * i + 1, nUnknown1 + 2 * i + 1, ((R[4] + R[7] * div_Z_Y)*ZZ - (R[5] + R[8] * div_Z_Y)*YY) / ZZ / ZZ));

			L = phiY - YY / ZZ;
			eigL[4 * i + 1] = L;

			//pNormal(pParams,nUnknown,L,A_T_P_A,A_T_P_L,1.);

			//xr,yr;
			//fx;
			phiX = phiY = 0.;
			for (int nx = 0; nx <= alongOrder; nx++)
			{
				double value = pow(pMatch[i].xr / (wi - 1), nx);
				tripletList.push_back(T(4 * i + 2, nx, -value));
				phiX += pUnknown[nx] * value;
			}
			tripletList.push_back(T(4 * i + 2, alongOrder + 1, -pMatch[i].yr / (hi - 1)));
			phiX += pUnknown[alongOrder + 1] * pMatch[i].yr / (hi - 1);

			for (int nx = 0; nx <= acrossOrder; nx++)
			{
				double value = pow(pMatch[i].xr / (wi - 1), nx);
				tripletList.push_back(T(4 * i + 3, nHalfUnknown1 + nx, -value));
				phiY += pUnknown[nHalfUnknown1 + nx] * value;
			}
			tripletList.push_back(T(4 * i + 3, nHalfUnknown1 + acrossOrder + 1, -pMatch[i].yr / (hi - 1)));
			phiY += pUnknown[nHalfUnknown1 + acrossOrder + 1] * pMatch[i].yr / (hi - 1);

			//pGeoModel[pMatch[i].nIndex[1]].getExtOrientationWithRu(pMatch[i].xr,pMatch[i].yr,XYZs,R,-1);
			pGeoModel[pMatch[i].nIndex[1]].GetCam2WGS84(R);
			pGeoModel[pMatch[i].nIndex[1]].GetCamPos(ep);
			XYZs[0] = ep[0], XYZs[1] = ep[1], XYZs[2] = ep[2];
			XX = R[0] * (X - XYZs[0]) + R[3] * (Y - XYZs[1]) + R[6] * (Z - XYZs[2]);
			YY = R[1] * (X - XYZs[0]) + R[4] * (Y - XYZs[1]) + R[7] * (Z - XYZs[2]);
			ZZ = R[2] * (X - XYZs[0]) + R[5] * (Y - XYZs[1]) + R[8] * (Z - XYZs[2]);

			tripletList.push_back(T(4 * i + 2, nUnknown1 + 2 * i, ((R[0] + R[6] * div_Z_X)*ZZ - (R[2] + R[8] * div_Z_X)*XX) / ZZ / ZZ));
			tripletList.push_back(T(4 * i + 2, nUnknown1 + 2 * i + 1, ((R[3] + R[6] * div_Z_Y)*ZZ - (R[5] + R[8] * div_Z_Y)*XX) / ZZ / ZZ));

			L = phiX - XX / ZZ;
			eigL[4 * i + 2] = L;
			//pNormal(pParams,nUnknown,L,A_T_P_A,A_T_P_L,1.);

			//fy
			//memset(pParams,0,sizeof(double)*nUnknown);

			//pParams[nUnknown1+2*i] = ((R[1]+R[7]*div_Z_X)*ZZ-(R[2]+R[8]*div_Z_X)*YY)/ZZ/ZZ;
			//pParams[nUnknown1+2*i+1] = ((R[4]+R[7]*div_Z_Y)*ZZ-(R[5]+R[8]*div_Z_Y)*YY)/ZZ/ZZ;
			tripletList.push_back(T(4 * i + 3, nUnknown1 + 2 * i, ((R[1] + R[7] * div_Z_X)*ZZ - (R[2] + R[8] * div_Z_X)*YY) / ZZ / ZZ));
			tripletList.push_back(T(4 * i + 3, nUnknown1 + 2 * i + 1, ((R[4] + R[7] * div_Z_Y)*ZZ - (R[5] + R[8] * div_Z_Y)*YY) / ZZ / ZZ));

			L = phiY - YY / ZZ;
			eigL[4 * i + 3] = L;

			//pNormal(pParams,nUnknown,L,A_T_P_A,A_T_P_L,1.);

		}

		SparseMatrixType eigA(nMatch * 4, nUnknown);//����Ŀ��  
		eigA.setFromTriplets(tripletList.begin(), tripletList.end());//��Triplet�й���ϡ�����  
		SparseMatrixType eigA_T = SparseMatrixType(eigA.transpose());
		SparseMatrixType eigA_T_P_A = eigA_T*eigA;

		//MatrixXd A_T_P_A = eigA_T_P_A.toDense();

		//EigenSolver<MatrixXd> es(A_T_P_A);
		//cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
		//MatrixXcd  evecs = es.eigenvectors();
		//eigA_T_P_A.

		VectorXd A_T_P_L = eigA_T*eigL;

		SimplicialLLT <SparseMatrix<double>> LU;
		LU.compute(eigA_T_P_A);
		if (LU.info() != Success)
		{
			printf("=>failed to solve the sparse eqation!\n");
			break;
		}
		VectorXd eigUnknown = LU.solve(A_T_P_L);
		//VectorXd eigUnknown;
		//sparse_GaussExt(eigA_T_P_A,A_T_P_L,eigUnknown,nUnknown);

		if (LU.info() != Success)
		{
			printf("=>failed to solve the sparse eqation!\n");
			break;
		}

		printf("=>iterate %d: %.15lf\n", nIter, eigUnknown[0]);

		bool bBreak = true;
		for (int n = 0; n < nUnknown; n++)
		{
			pUnknown[n] += eigUnknown[n];

			if (fabs(eigUnknown[n]) > 1.e-7)
				bBreak = false;
		}

		if (bBreak)
			break;

		nIter++;

		if (nIter > 100)
		{
			printf("=>iterate number is more than 100!\n");
			break;
		}


	} while (1);

	if (pRes)
		delete[]pRes, pRes = NULL;
	pRes = new double[nUnknown1];
	memcpy(pRes, pUnknown, sizeof(double)*nUnknown1);

	////start������ڷ�λ֮��

	//DistortionParams params;
	//params.xOrder = xOrder;
	//params.yOrder = yOrder;

	//memcpy(params.px, pRes, sizeof(double)*(params.xOrder + 2));
	//memcpy(params.py, pRes + params.xOrder + 2, sizeof(double)*(params.yOrder + 2));

	//pGeoModel[0].getSensorInfor().setDistortionParams(params);
	//pGeoModel[1].getSensorInfor().setDistortionParams(params);

	//FILE* fpTest = fopen("c:\\temp\\after_distortion.txt", "w");
	//fprintf(fpTest, "%d\n", nMatch);
	//double minx, maxx, miny, maxy, rmsx, rmsy;
	//rmsx = rmsy = 0.;
	//maxx = maxy = 0;
	//minx = miny = 999999999.;

	//int nIndex = 0;
	//for (int i = 0; i < nMatch; i++)
	//{
	//	double lat1, lon1, h1, lat2, lon2, h2;
	//	h1 = pGeoModel[0].fromxyh2latlon(pMatch[i].xl, pMatch[i].yl, pH[i], lat1, lon1, -1, false);
	//	if (fabs(h1 + 99999.) < 1.e-6)
	//		continue;

	//	h2 = pGeoModel[1].fromxyh2latlon(pMatch[i].xr, pMatch[i].yr, pH[i], lat2, lon2, -1, false);
	//	if (fabs(h2 + 99999.) < 1.e-6)
	//		continue;

	//	double ex = (lon2 - lon1) * 110000 / 1.98;
	//	double ey = (lat2 - lat1) * 110000 / 1.98;

	//	minx = min(minx, fabs(ex));
	//	miny = min(miny, fabs(ey));

	//	maxx = max(maxx, fabs(ex));
	//	maxy = max(maxy, fabs(ey));

	//	rmsx += ex*ex;
	//	rmsy += ey*ey;

	//	nIndex++;

	//	fprintf(fpTest, "%04d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", i, pMatch[i].xl, pMatch[i].yl, pMatch[i].xr, pMatch[i].yr, ex, ey);
	//}
	//double plane = sqrt((rmsx + rmsy) / nIndex);
	//rmsx = sqrt(rmsx / nIndex);
	//rmsy = sqrt(rmsy / nIndex);
	//fprintf(fpTest, "x: %lf\t%lf\t%lf\n", minx, maxx, rmsx);
	//fprintf(fpTest, "y: %lf\t%lf\t%lf\n", miny, maxy, rmsy);
	//fprintf(fpTest, "plane: %lf", plane);
	//fclose(fpTest);

	//delete[]pH, pH = NULL;
	//delete[]pUnknown, pUnknown = NULL;

	////end������ڷ�λ֮��

	return true;
}

