/**********************************************************************
 *
 * sstPostgis01Lib - library for creating Postgis SQL Import Statements
 * Hosted on github
 *
 * Copyright (C) 2021 Hans Ulrich Rehr, Hanover, Germany
 *
 * This is free software; you can redistribute and/or modify it under
 * the terms of the GNU Lesser General Public Licence as published
 * by the Free Software Foundation.
 * See the COPYING file for more information.
 *
 **********************************************************************/
// sstPostgis01Sql1.cpp    19.07.21  Re.    03.01.17  Re.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstMath01Lib.h>
#include <sstStr01Lib.h>
#include <sstStr01FixColWidth.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstPostgis01Lib.h>

//=============================================================================
sstPostGis01_CvtSqlStr::sstPostGis01_CvtSqlStr()
{

}
//=============================================================================
int sstPostGis01_CvtSqlStr::AppendCoor2String (int             iKey,
                                               double          dXX,
                                               double          dYY,
                                               std::string    *oSQL_Str)
//-----------------------------------------------------------------------------
{
  std::string sDoubleStr;
  sstStr01FcwCls oStrCnvt;

  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  // append x-value and y-value to SQL-String

  char cDblFrmt[10];
  strncpy(cDblFrmt,"%12.2f",10);

  // write X double right bordered to length 14 string
  sDoubleStr.clear();
  oStrCnvt.SetReadPositon(0,1);
  iStat = oStrCnvt.DblFrmt2String(0, 14,  dXX, cDblFrmt, &sDoubleStr);

  *oSQL_Str += sDoubleStr;
  *oSQL_Str += " ";

  // write Y double right bordered to length 14 string
  sDoubleStr.clear();
  oStrCnvt.SetReadPositon(0,1);
  iStat = oStrCnvt.DblFrmt2String( 0, 14,  dYY, cDblFrmt, &sDoubleStr);
  *oSQL_Str += sDoubleStr;

  return iStat;
}
//=============================================================================
//int sstPostGis01_CvtSqlStr::PR_PointCoor2String (int                  iKey,
//                                                 PtsDssBase_Cls   *oPtssDB,
//                                                 dREC04RECNUMTYP   dPR_RecNum,
//                                                 std::string      *oSQL_Str)
////-----------------------------------------------------------------------------
//{
//  unsigned long dRecNumMain;
//  dREC04RECNUMTYP dRecNumPK;
//  sstPostGis01_CvtSqlStr oCvtSqlStr;

//  PtssTypPRCls  oPR_Rec;
//  PtssTypPKCls  oPK_Rec;

//  int iStat = 0;
////-----------------------------------------------------------------------------
//  if ( iKey != 0) return -1;

//  char cDblFrmt[10];
//  strncpy(cDblFrmt,"%12.2f",10);

//  // Read PR record from table with record number
//  dRecNumMain = 0;
//  oPtssDB->ReadDbPR(0,dPR_RecNum,&oPR_Rec,&dRecNumMain);

//  // Seach PointNumber in Table PK <BR>
//  dRecNumPK = 0;
//  iStat = oPtssDB->SeachPointNumberTablePK ( 0, oPR_Rec.PR2, &oPK_Rec, &dRecNumPK);
//  if (iStat < 0) return -2;

//  // write coordinates to new string <BR>
//  iStat = oCvtSqlStr.AppendCoor2String( 0, oPK_Rec.dXX, oPK_Rec.dYY, oSQL_Str);

//  return iStat;
//}
//=============================================================================
sstPGisTableMemberCls::sstPGisTableMemberCls()
{
  this->MemberName.clear();
  this->MemberType.clear();
}
//=============================================================================
std::string sstPGisTableMemberCls::getMemberName() const
{
return MemberName;
}
//=============================================================================
void sstPGisTableMemberCls::setMemberName(const std::string &value)
{
MemberName = value;
}
//=============================================================================
std::string sstPGisTableMemberCls::getMemberType() const
{
return MemberType;
}
//=============================================================================
void sstPGisTableMemberCls::setMemberType(const std::string &value)
{
MemberType = value;
}
//=============================================================================
sstPGisSampleBaseCls::sstPGisSampleBaseCls(sstMisc01AscFilCls *poTmpSqlFile, const std::string oTmpTabNam)
{
  this->EPSG.clear();
  this->oTableMemberVector.clear();
  this->poSqlFile = poTmpSqlFile;
  this->oTabNam = oTmpTabNam;
  this->oSqlStr.clear();
  this->oStatementStr.clear();
  this->uiActTabRec = 0;
}
//=============================================================================
std::string sstPGisSampleBaseCls::getEPSG() const
{
return EPSG;
}
//=============================================================================
void sstPGisSampleBaseCls::setEPSG(const std::string &value)
{
EPSG = value;
}
//=============================================================================
int sstPGisSampleBaseCls::SetTableMember(int iKey,const std::string oMemberName, const std::string oMemberType)
{
  // int iRet = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------
  if ( iKey != 0) return -1;

  sstPGisTableMemberCls oTableMember;
  oTableMember.setMemberName(oMemberName);
  oTableMember.setMemberType(oMemberType);
  this->oTableMemberVector.push_back(oTableMember);
  this->uiActTabRec = 0;
  return iStat;
}
//=============================================================================
std::string sstPGisSampleBaseCls::getTabNam() const
{
  return oTabNam;
}
//=============================================================================
void sstPGisSampleBaseCls::setTabNam(const std::string &value)
{
  oTabNam = value;
}
//=============================================================================
std::string sstPGisSampleBaseCls::getSqlStr() const
{
return oSqlStr;
}
//=============================================================================
void sstPGisSampleBaseCls::setSqlStr(const std::string &value)
{
oSqlStr = value;
}
//=============================================================================
int sstPGisSampleBaseCls::SqlSampleRowInsertStartGID( unsigned long ulGID)
{
  sstStr01Cls oCsvCnvt;
  int iStat = 0;

  this->oStatementStr = "INSERT INTO ";
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.SetSeparator(0,(char*)"");

  this->oStatementStr += this->getTabNam() + " (";

  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;

  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    this->oStatementStr += oTableMember.getMemberName();
    if (it != finalIter)
    {
      this->oStatementStr += ",";
    }
  }

  this->oStatementStr += ") VALUES ( ";

  // write Geometry number as GID to sql string if not null
  this->uiActTabRec = 0;
  if (ulGID > 0)
  {
    oCsvCnvt.SetReadPositon(0,0);
    iStat = oCsvCnvt.Csv_Int4_2String(0,ulGID, &this->oStatementStr);
    this->uiActTabRec++;  // now first value is set in statement
    this->oSqlStr = this->oStatementStr;
  }

  return iStat;
}
//=============================================================================
int sstPGisSampleBaseCls::SqlSampleRowInsertString(const std::string oValStr)
{
  this->uiActTabRec++;  /**< Actual Insert value  */
  sstStr01Cls oCsvCnvt;
  // write attribute name to sql string
  oCsvCnvt.SetSeparatorTyp(0,1);
  oCsvCnvt.SetBracket(0,(char*)"'");
  if (this->uiActTabRec > 1) {
    oCsvCnvt.SetSeparator(0,(char*)",");
  } else {
    this->oSqlStr = this->oStatementStr;  // copy constant sql statement string to sql output string
    oCsvCnvt.SetSeparator(0,(char*)"");
  }
  int iStat = oCsvCnvt.Csv_Str_2String(0,oValStr,&this->oSqlStr);  // add next value to sql output string
  return iStat;
}
//=============================================================================
int sstPGisSampleBaseCls::SqlSampleRowInsertUnsignedLong(const unsigned long ulVal)
{
  this->uiActTabRec++;  /**< Actual Insert value  */
  sstStr01Cls oCsvCnvt;
  // write attribute name to sql string
  oCsvCnvt.SetSeparatorTyp(0,1);
  oCsvCnvt.SetBracket(0,(char*)"'");
  oCsvCnvt.SetSeparator(0,(char*)",");
  // oCsvCnvt.setDecType(1);  // decimal point
  oCsvCnvt.SetReadPositon(0,0);
  int iStat = oCsvCnvt.Csv_Int4_2String(0,ulVal, &this->oSqlStr);
  return iStat;
}
//=============================================================================
int sstPGisSampleBaseCls::SqlSampleRowInsertDouble(const double dValStr)
{
    this->uiActTabRec++;  /**< Actual Insert value  */
  sstStr01Cls oCsvCnvt;
  // write attribute name to sql string
  oCsvCnvt.SetSeparatorTyp(0,1);
  oCsvCnvt.SetBracket(0,(char*)"'");
  oCsvCnvt.SetSeparator(0,(char*)",");
  oCsvCnvt.setDecType(1);  // decimal point
  int iStat = oCsvCnvt.Csv_Dbl_2String( 0, dValStr, &this->oSqlStr);
  return iStat;
}
//=============================================================================
int sstPGisSampleBaseCls::SqlSampleRowDropTable()
{
  std::string oSqlStr;
  oSqlStr = "DROP TABLE ";
  oSqlStr += this->getTabNam();
  oSqlStr += ";";
  this->poSqlFile->Wr_StrDS1(0, &oSqlStr);
  return 0;
}
//=============================================================================
int sstPGisSampleBaseCls::SqlSampleRowTruncTable()
{
  std::string oSqlStr;
  oSqlStr = "TRUNCATE TABLE ";
  oSqlStr += this->getTabNam();
  oSqlStr += ";";
  this->poSqlFile->Wr_StrDS1(0, &oSqlStr);
  return 0;
}
//=============================================================================
sstPGisSampleStringCls::sstPGisSampleStringCls(sstMisc01AscFilCls *poSqlFile,
                                             const std::string oTmpTabNam):
  sstPGisSampleBaseCls(poSqlFile,oTmpTabNam)
{

}
//=============================================================================
int sstPGisSampleStringCls::SqlSampleRowCreateTable()
{
  // std::string sSqlStr = "CREATE TABLE Abzw ( gid serial primary key, DBS varchar(20), geom geometry(POINT) );";
  std::string sSqlStr = "CREATE TABLE";
  sSqlStr += " " + this->getTabNam();
  sSqlStr += " (";
  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;
  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += " " + oTableMember.getMemberName();
    sSqlStr += " " + oTableMember.getMemberType();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }
  sSqlStr +=  " );";

  this->poSqlFile->Wr_StrDS1(0, &sSqlStr);
  return 0;
}
//=============================================================================
int sstPGisSampleStringCls::SqlSampleRowInsertEnd()
{
  std::string oDoubleStr;
  sstStr01Cls oCsvCnvt;

  // finish string
  oCsvCnvt.SetSeparator(0,(char*)"");
  oDoubleStr =  ");";
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&this->oSqlStr);

  int iStat = poSqlFile->Wr_StrDS1( 0, &this->oSqlStr);
  this->uiActTabRec = 0;
  this->oSqlStr.clear();
  return iStat;
}
//=============================================================================
sstPGisSamplePointCls::sstPGisSamplePointCls(sstMisc01AscFilCls *poSqlFile,
                                             const std::string oTmpTabNam):
  sstPGisSampleBaseCls(poSqlFile,oTmpTabNam)
{

}
//=============================================================================
int sstPGisSamplePointCls::SqlSampleRowCreatePoint()
{
  // std::string sSqlStr = "CREATE TABLE Abzw ( gid serial primary key, DBS varchar(20), geom geometry(POINT) );";
  std::string sSqlStr = "CREATE TABLE";
  sSqlStr += " " + this->getTabNam();
  sSqlStr += " (";
  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;
  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += " " + oTableMember.getMemberName();
    sSqlStr += " " + oTableMember.getMemberType();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }
  sSqlStr +=  " );";

  this->poSqlFile->Wr_StrDS1(0, &sSqlStr);
  return 0;
}
//=============================================================================
int sstPGisSamplePointCls::SqlSampleRowInsertPoint(unsigned long     ulVal,
                                                   const std::string oValStr,
                                                   sstMath01dPnt3Cls oPnt)
{
  std::string sSqlStr;
  std::string oDoubleStr;
  sstStr01Cls oCsvCnvt;

  sSqlStr = "INSERT INTO ";
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.SetSeparator(0,(char*)"");

  sSqlStr += this->getTabNam() + " (";

  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;

  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += oTableMember.getMemberName();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }

  sSqlStr += ") VALUES ( ";

  // write polygon number as GID to sql string
  oCsvCnvt.SetReadPositon(0,0);
  oCsvCnvt.Csv_Int4_2String(0,ulVal,&sSqlStr);

  // write attribute name to sql string
  oCsvCnvt.SetSeparatorTyp(0,1);
  oCsvCnvt.SetBracket(0,(char*)"'");
  oCsvCnvt.SetSeparator(0,(char*)",");
  oCsvCnvt.Csv_Str_2String(0,oValStr,&sSqlStr);
  // sSqlStr2 += this->

  // write geometry type to sql string
  oDoubleStr = "ST_GeomFromText('POINT(";

  // write for example 32540694.64 5804147.73 to oDoubleStr
  sstPostGis01_CvtSqlStr oSqlCvt;
  oSqlCvt.AppendCoor2String(0,oPnt.x,oPnt.y,&oDoubleStr);
  oDoubleStr += ")' ";
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);

  // write SRID and finish string
  oDoubleStr = this->getEPSG() + ")  );";
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);

  poSqlFile->Wr_StrDS1( 0, &sSqlStr);
  return 0;
}
//=============================================================================
int sstPGisSamplePointCls::SqlSampleRowInsertPointEnd(sstMath01dPnt3Cls oPnt)
{
  std::string oDoubleStr;
  sstStr01Cls oCsvCnvt;

  // write geometry type to sql string
  oDoubleStr = "ST_GeomFromText('POINT(";

  // write for example 32540694.64 5804147.73 to oDoubleStr
  sstPostGis01_CvtSqlStr oSqlCvt;
  oSqlCvt.AppendCoor2String(0,oPnt.x,oPnt.y,&oDoubleStr);
  oDoubleStr += ")' ";
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.SetSeparator(0,(char*)",");
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&this->oSqlStr);

  // write SRID and finish string
  oDoubleStr = this->getEPSG() + ")  );";
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&this->oSqlStr);

  int iStat = poSqlFile->Wr_StrDS1( 0, &this->oSqlStr);
  this->oSqlStr.clear();
  this->uiActTabRec = 0;
  return iStat;
}
//=============================================================================
sstPGisSampleLinestringCls::sstPGisSampleLinestringCls(sstMisc01AscFilCls *poSqlFile,
                                                       const std::string oTmpTabNam)
  :sstPGisSampleBaseCls(poSqlFile,oTmpTabNam)
{

}
//=============================================================================
int sstPGisSampleLinestringCls::SqlSampleRowCreateLinestring()
{
  std::string sSqlStr = "CREATE TABLE";
  sSqlStr += " " + this->getTabNam();
  sSqlStr += " (";
  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;
  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += " " + oTableMember.getMemberName();
    sSqlStr += " " + oTableMember.getMemberType();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }
  sSqlStr +=  " );";

  this->poSqlFile->Wr_StrDS1(0, &sSqlStr);
  return 0;
}
//=============================================================================
int sstPGisSampleLinestringCls::SqlSampleRowInsertLinestring(unsigned long ulVal, const std::string oValStr,
                                                   std::vector<sstMath01dPnt3Cls> *poPntVector)
{
  std::string sSqlStr;
  std::string oDoubleStr;
  sstStr01Cls oCsvCnvt;
  int iStat = 0;

  // write first row of linestring to sql file
  // INSERT INTO LA ( gid, DBS, geom) VALUES ( 1,'8100000000000',ST_GeomFromText('LINESTRING(


  sSqlStr = "INSERT INTO ";
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.SetSeparator(0,(char*)"");

  sSqlStr += this->getTabNam() + " (";

  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;

  // Write list of member names in string
  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += " " + oTableMember.getMemberName();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }

  sSqlStr += ") VALUES ( ";

  // write polygon number as GID to sql string
  oCsvCnvt.SetReadPositon(0,0);
  oCsvCnvt.Csv_Int4_2String(0,ulVal,&sSqlStr);

  // write second member value attribute name to sql string
  oCsvCnvt.SetSeparatorTyp(0,1);
  oCsvCnvt.SetBracket(0,(char*)"'");
  oCsvCnvt.SetSeparator(0,(char*)",");
  oCsvCnvt.Csv_Str_2String(0,oValStr,&sSqlStr);

  // write geometry type to sql string
  oDoubleStr = "ST_GeomFromText('LINESTRING(";

  sstPostGis01_CvtSqlStr oSqlCvt;
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);
  poSqlFile->Wr_StrDS1( 0, &sSqlStr);
  sSqlStr.clear();

  //=== Write coordinate rows to sql file
  std::vector<sstMath01dPnt3Cls>::iterator finalIter2 = poPntVector->end();
  finalIter2--;  //

  for (std::vector<sstMath01dPnt3Cls>::iterator it = poPntVector->begin();
                                                    it != poPntVector->end(); ++it)
  {
    sstMath01dPnt3Cls oPnt = *it;
    sSqlStr.clear();
    oDoubleStr.clear();
    oCsvCnvt.SetSeparatorTyp(0,0);
    oCsvCnvt.SetBracket(0,(char*)"");
    oSqlCvt.AppendCoor2String(0,oPnt.x,oPnt.y,&oDoubleStr);
    oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);

    if (it != finalIter2)
    {
      sSqlStr += ",";
    }
    poSqlFile->Wr_StrDS1( 0, &sSqlStr);
    sSqlStr.clear();
  }

  // write SRID and finish string
  oDoubleStr = ")' ,";
  oDoubleStr += this->getEPSG() + ")  );";
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);
  poSqlFile->Wr_StrDS1( 0, &sSqlStr);

  return iStat;
}
//=============================================================================
sstPGisSamplePolygonCls::sstPGisSamplePolygonCls(sstMisc01AscFilCls *poSqlFile,
                                                 const std::string oTmpTabNam)
  :sstPGisSampleBaseCls(poSqlFile,oTmpTabNam)
{

}
//=============================================================================
int sstPGisSamplePolygonCls::SqlSampleRowCreatePolygon()
{
  std::string sSqlStr = "CREATE TABLE";
  sSqlStr += " " + this->getTabNam();
  sSqlStr += " (";
  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;
  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += " " + oTableMember.getMemberName();
    sSqlStr += " " + oTableMember.getMemberType();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }
  sSqlStr +=  " );";

  this->poSqlFile->Wr_StrDS1(0, &sSqlStr);
  return 0;
}
//=============================================================================
int sstPGisSamplePolygonCls::SqlSampleRowInsertPolygon(unsigned long ulVal, const std::string oValStr,
                                                   std::vector<sstMath01dPnt3Cls> *poPntVector)
{
  std::string sSqlStr;
  std::string oDoubleStr;
  sstStr01Cls oCsvCnvt;
  int iStat = 0;

  // write first row of linestring to sql file
  // INSERT INTO LA ( gid, DBS, geom) VALUES ( 1,'8100000000000',ST_GeomFromText('LINESTRING(


  sSqlStr = "INSERT INTO ";
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.SetSeparator(0,(char*)"");

  sSqlStr += this->getTabNam() + " (";

  std::vector<sstPGisTableMemberCls>::iterator finalIter = this->oTableMemberVector.end();
  finalIter--;

  // Write list of member names in string
  for (std::vector<sstPGisTableMemberCls>::iterator it = this->oTableMemberVector.begin();
                                                    it != this->oTableMemberVector.end(); ++it)
  {
    sstPGisTableMemberCls oTableMember = *it;
    sSqlStr += " " + oTableMember.getMemberName();
    if (it != finalIter)
    {
      sSqlStr += ",";
    }
  }

  sSqlStr += ") VALUES ( ";

  // write polygon number as GID to sql string
  oCsvCnvt.SetReadPositon(0,0);
  oCsvCnvt.Csv_Int4_2String(0,ulVal,&sSqlStr);

  // write second member value attribute name to sql string
  oCsvCnvt.SetSeparatorTyp(0,1);
  oCsvCnvt.SetBracket(0,(char*)"'");
  oCsvCnvt.SetSeparator(0,(char*)",");
  oCsvCnvt.Csv_Str_2String(0,oValStr,&sSqlStr);

  // write geometry type to sql string
  oDoubleStr = "ST_GeomFromText('POLYGON((";

  sstPostGis01_CvtSqlStr oSqlCvt;
  oCsvCnvt.SetSeparatorTyp(0,0);
  oCsvCnvt.SetBracket(0,(char*)"");
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);
  poSqlFile->Wr_StrDS1( 0, &sSqlStr);
  sSqlStr.clear();

  //=== Write coordinate rows to sql file
  std::vector<sstMath01dPnt3Cls>::iterator finalIter2 = poPntVector->end();
  finalIter2--;  //

  for (std::vector<sstMath01dPnt3Cls>::iterator it = poPntVector->begin();
                                                    it != poPntVector->end(); ++it)
  {
    sstMath01dPnt3Cls oPnt = *it;
    sSqlStr.clear();
    oDoubleStr.clear();
    oCsvCnvt.SetSeparatorTyp(0,0);
    oCsvCnvt.SetBracket(0,(char*)"");
    oSqlCvt.AppendCoor2String(0,oPnt.x,oPnt.y,&oDoubleStr);
    oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);

    if (it != finalIter2)
    {
      sSqlStr += ",";
    }
    poSqlFile->Wr_StrDS1( 0, &sSqlStr);
    sSqlStr.clear();
  }

  // write SRID and finish string
  oDoubleStr = "))' ,";
  oDoubleStr += this->getEPSG() + ")  );";
  oCsvCnvt.Csv_Str_2String(0,oDoubleStr,&sSqlStr);
  poSqlFile->Wr_StrDS1( 0, &sSqlStr);

  return iStat;
}
//=============================================================================
