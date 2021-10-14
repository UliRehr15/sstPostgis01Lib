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
// sstDxf2Postgis01.cpp    14.10.21  Re.    01.10.21  Re.
//
// App converts Dxf Data to Postgis SQL Import File.
// Test with File TestPoint.dxf from sstDxf03LibTest.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstMath01Lib.h>
#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstDxf03Lib.h>
#include <sstPostgis01Lib.h>

#include "sstDxf2Postgis01.h"

int main ()
//=============================================================================
{
  int iRet = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------

  // Open Protocol
  sstMisc01PrtFilCls oPrt;
  iStat = oPrt.SST_PrtAuf( 1, (char*)"sstDxf2Postgis01.prt");
  assert(iStat >= 0);

  //===========================================================================
  // Open new sstDxf Database
  sstDxf03DbCls oDxfDB(&oPrt);

  // import content of dxf file into sstDxf database
  // iStat = oDxfDB.ReadAllFromDxf(0,"TestArc.dxf");
  // iStat = oDxfDB.ReadAllFromDxf(0,"TestPolyline.dxf");
  iStat = oDxfDB.ReadAllFromDxf(0,"TestPoint.dxf");
  if (iStat < 0)
  {
    // Close Protocol
    int iStat1 = oPrt.SST_PrtZu( 1);
    assert(iStat1 >= 0);
    return iStat;
  }
  // assert(iStat >= 0);

  dREC04RECNUMTYP dEntRecs = 0;
  dREC04RECNUMTYP dMainRecs = 0;

  dMainRecs = oDxfDB.MainCount();
  // assert(dMainRecs == 47);

  dEntRecs = oDxfDB.EntityCount(RS2::EntityPoint);
  if (dEntRecs <= 0)
  {
    // Close Protocol
    int iStat1 = oPrt.SST_PrtZu( 1);
    assert(iStat1 >= 0);
    return iStat;
  }
  // assert(dEntRecs > 0);


  //===========================================================================

  sstMisc01AscFilCls oPGisSqlFile;

  oPGisSqlFile.fopenWr(0,"Test2.sql");
  oPrt.SST_PrtWrtChar( 1, (char*)"SQL Write File opened", (char*)"Test2.sql -");

  sstPGisSamplePointCls oSamplePoint(&oPGisSqlFile,"Point");
  sstPGisSampleLinestringCls oSampleLinestring(&oPGisSqlFile,"Linestring");
  sstPGisSamplePolygonCls oSamplePolygon(&oPGisSqlFile,"Hatch");

  oSamplePoint.setEPSG("3456");
  oSampleLinestring.setEPSG("3456");
  oSamplePolygon.setEPSG("3456");

  oSamplePoint.SetTableMember(0,"gid","serial primary key");
  oSamplePoint.SetTableMember(0,"Layer","varchar(20)");
  oSamplePoint.SetTableMember(0,"Linetype","varchar(20)");
  oSamplePoint.SetTableMember(0,"handle","varchar(20)");
  oSamplePoint.SetTableMember(0,"geom","geometry(POINT)");

  // Sample SQL Create Point Row
  oSamplePoint.SqlSampleRowCreatePoint();
  oPrt.SST_PrtWrtChar( 1, (char*)"POINT Create Table / Insert Statement", (char*)"Test checked: ");

  DL_PointData oDLPoint;               // Entity Point from dxflib
  DL_Attributes oDLAttributes;         // Class Dxf Attributes from dxflib

  // dREC04RECNUMTYP dRecNo = 1;
  dREC04RECNUMTYP dRecNo = 1;
  for (dRecNo = 1; dRecNo <= dEntRecs; dRecNo++)
  {
    iStat = oDxfDB.ReadPoint( 0, dRecNo, &oDLPoint, &oDLAttributes);
    assert(iStat >= 0);

    // Sample SQL Insert Point Row
    sstMath01dPnt3Cls dPnt;
    dPnt.Set(oDLPoint.x, oDLPoint.y,0.0);
    oSamplePoint.SetTableValue( 3, oDLAttributes.getLinetype());
    oSamplePoint.SetTableValueInt2( 4, oDLAttributes.getHandle());
    oSamplePoint.SqlSampleRowInsertPoint( 1, oDLAttributes.getLayer(), dPnt);
  }

  // Close SQL file after full writing
  oPGisSqlFile.fcloseFil(0);
  oPrt.SST_PrtWrtChar( 1, (char*)"SQL Write File closed", (char*)"Test2.sql -");

  // Reopen File Test2.sql
  iStat = oPGisSqlFile.fopenRd(0,"Test2.sql");
  assert(iStat >= 0);

  // Read lines from file and compare file rows with wished result
  std::string oSqlFileStr;
  // Read and compare first row in File
  iStat = oPGisSqlFile.Rd_StrDS1( 0, &oSqlFileStr);
  assert(iStat >= 0);
  iStat = oSqlFileStr.compare("CREATE TABLE Point ( gid serial primary key, Layer varchar(20), Linetype varchar(20), handle varchar(20), geom geometry(POINT) );");
  assert(iStat == 0);

  // Read and compare second row in File
  iStat = oPGisSqlFile.Rd_StrDS1( 0, &oSqlFileStr);
  assert(iStat >= 0);
  iStat = oSqlFileStr.compare("INSERT INTO Point (gid,Layer,Linetype,handle,geom) VALUES ( 1,'0','BYLAYER','48',ST_GeomFromText('POINT(100.00 100.00)' ,3456)  );");
  assert(iStat == 0);

  // Close file
  oPGisSqlFile.fcloseFil(0);
  oPrt.SST_PrtWrtChar( 1, (char*)"SQL Read/Compare File closed", (char*)"Test2.sql -");

  // Close Protocol
  iStat = oPrt.SST_PrtZu( 1);

  // Fatal Errors goes to an assert
  // assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
