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
// sstPostgis01LibTest.cpp    19.07.21  Re.    26.06.18  Re.
//
// testframe for sstPostgis01Lib

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <string>

#include <sstMath01Lib.h>
#include <sstStr01Lib.h>
#include <sstMisc01Lib.h>
#include <sstRec04Lib.h>
#include <sstPostgis01Lib.h>

#include "sstPostgis01LibTest.h"

int main ()
//=============================================================================
{
  int iRet = 0;
  int iStat = 0;
//-----------------------------------------------------------------------------

  // Open Protocol
  sstMisc01PrtFilCls oPrt;
  iStat = oPrt.SST_PrtAuf( 1, (char*)"sstPostgis01LibTest.prt");
  assert(iStat >= 0);

  sstMisc01AscFilCls oPGisSqlFile;

  oPGisSqlFile.fopenWr(0,"Test2.sql");
  oPrt.SST_PrtWrtChar( 1, (char*)"SQL Write File opened", (char*)"Test2.sql -");

  sstPGisSamplePointCls oSamplePoint(&oPGisSqlFile,"Form");
  sstPGisSampleLinestringCls oSampleLinestring(&oPGisSqlFile,"LA");
  sstPGisSamplePolygonCls oSamplePolygon(&oPGisSqlFile,"Flaeche");

  oSamplePoint.setEPSG("3456");
  oSampleLinestring.setEPSG("3456");
  oSamplePolygon.setEPSG("3456");

  oSamplePoint.SetTableMember(0,"gid","serial primary key");
  oSamplePoint.SetTableMember(0,"DBS","varchar(20)");
  oSamplePoint.SetTableMember(0,"geom","geometry(POINT)");

  // Sample SQL Create Point Row
  oSamplePoint.SqlSampleRowCreatePoint();
  oPrt.SST_PrtWrtChar( 1, (char*)"Create POINT", (char*)"Test checked: ");

  // Sample SQL Insert Point Row
  sstMath01dPnt3Cls dPnt;
  dPnt.Set(32539500.00, 5802600.00,0.0);
  oSamplePoint.SqlSampleRowInsertPoint( 1, "8100000000000", dPnt);

  // Sample SQL Create Point Row
  oSampleLinestring.SetTableMember(0,"gid","serial primary key");
  oSampleLinestring.SetTableMember(0,"DBS","varchar(20)");
  oSampleLinestring.SetTableMember(0,"geom","geometry(LINESTRING)");
  iStat = oSampleLinestring.SqlSampleRowCreateLinestring();

  // Sample SQL Insert Point Row
  std::vector<sstMath01dPnt3Cls> oPntVector;
  sstMath01dPnt3Cls oPnt;
  oPnt.Set(32539500.00, 5802600.00,0.0);
  oPntVector.push_back(oPnt);
  oPnt.Set(32539600.00, 5802500.00,0.0);
  oPntVector.push_back(oPnt);
  oPnt.Set(32539700.00, 5802400.00,0.0);
  oPntVector.push_back(oPnt);

  iStat = oSampleLinestring.SqlSampleRowInsertLinestring( 1, "8100000000000", &oPntVector);
  oPrt.SST_PrtWrtChar( 1, (char*)"Create LINESTRING", (char*)"Test checked: ");


  oPGisSqlFile.fcloseFil(0);
  oPrt.SST_PrtWrtChar( 1, (char*)"SQL Write File closed", (char*)"Test2.sql -");

  // Close Protocol
  iStat = oPrt.SST_PrtZu( 1);

  // Fatal Errors goes to an assert
  // assert(iRet >= 0);

  // Small Errors will given back
  iRet = iStat;

  return iRet;
}
//=============================================================================
