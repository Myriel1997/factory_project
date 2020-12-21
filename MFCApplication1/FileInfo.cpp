#include "FileInfo.h"

CFileInfo::CFileInfo(void)
{
}

CFileInfo::~CFileInfo(void)
{
}
///////////////////////////////binĿ¼·��///////////////////////////////////////////
bool CFileInfo::GetCurrentAppPath(char **path)
{
	char str[MAX_PATH], drive[MAX_PATH], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];

	GetModuleFileName(NULL, str, sizeof(str));
	_splitpath_s(str, drive, dir, fname, ext);
	strcat_s(drive, dir);
	strcpy_s(m_CurrentPath,drive);
	*path = m_CurrentPath;

	return true;
}
////////////////////////////////Model���ļ�·��//////////////////////////////////////////
CString CFileInfo::GetModelPath(int pro_index,int camIndex)
{
	char* dir=NULL;
	GetCurrentAppPath(&dir);
	//model·��

	m_strModelPath.Format("%sModel\\model%d",dir,pro_index);
	m_strModelIniPath.Format("%s\\checkpara-%d.ini",m_strModelPath,camIndex);
	return m_strModelIniPath;

}
CString CFileInfo::GetModelPathUP(int pro_index)
{
	char* dir=NULL;
	GetCurrentAppPath(&dir);
	//model·��

	m_strModelPath.Format("%sModel\\model%d\\",dir,pro_index);
	return m_strModelPath;

}
CString CFileInfo::GetCamPath(int camIndex)
{
	char* dir=NULL;
	GetCurrentAppPath(&dir);
	//model·��
	m_strModelPath.Format("%sModel",dir);
	m_strCamPath.Format("%s\\Dalas-%d.ini",m_strModelPath,camIndex);
	return m_strCamPath;

}
//////////////////////////���ò�����usrer.ini����ȡ·��////////////////////////////////////////////////
CString CFileInfo::GetShareIniPath()
{
	char* dir=NULL;
	GetCurrentAppPath(&dir);
	m_strSharePath.Format("%sConfig\\user.ini",dir);
	return m_strSharePath;
}