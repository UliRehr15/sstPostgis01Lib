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
// sstPostgis01Lib.h   19.07.21  Re.   03.01.17  Re.
//
// Datastructures and Prototypes for system "sstPostgis01Lib"
//
// For using this lib please look at sstPostgis01LibTest.


#ifndef   _SSTPOSTGIS01LIB_H
#define   _SSTPOSTGIS01LIB_H

/**
 * @defgroup sstPostgis01Lib sstPostgis01Lib: cpp sst SQL classes for postgis
 *
 * cpp sst sql library <BR>
 *
 */



// Defines ---------------------------------------------------------------------

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

// Structures and Classes ------------------------------------------------------

//==============================================================================
/**
* @brief postgis converting to sql string class
*
* More Comment
*
* Changed: 13.06.16  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 13.06.16
*/
// ----------------------------------------------------------------------------
class sstPostGis01_CvtSqlStr
{
  public:   // Public functions
     sstPostGis01_CvtSqlStr();   // Constructor
    // ~X();   // Destructor
    //==============================================================================
    /**
    * @brief // append coordinates to existing string <BR>
    * iStat = oPostGis.AppendCoor2String ( iKey, &dXX, &dYY, &oSQL_Str);
    *
    * Result is string like 32540684.46 5804146.24
    *
    * @param iKey       [in] For the moment 0
    * @param dXX        [in] X double
    * @param dYY        [in] Y double
    * @param oSQL_Str   [in out] Coordinates string
    *
    * @return Errorstate
    *
    * @retval   =1: Record found
    * @retval   =0: Record not found
    * @retval   <0: Unspecified Error
    */
    //------------------------------------------------------------------------------
    int AppendCoor2String (int             iKey,
                           double          dXX,
                           double          dYY,
                           std::string    *oSQL_Str);
    //==============================================================================

  private:  // Private functions
  int Dum;        /**< Dummy */
};
//==============================================================================
/**
* @brief Definition Class sstPGisTableMemberCls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstPGisTableMemberCls
{
  public:   // Public functions
     sstPGisTableMemberCls();   // Constructor
    // ~X();   // Destructor
// ----------------------------------------------------------------------------
     //==============================================================================
     /**
     * @brief // Get Member Name <BR>
     * iStat = oPGisTableMember.getMemberName();
     *
     * @return value
     */
     // ----------------------------------------------------------------------------
     std::string getMemberName() const;
     //==============================================================================
     /**
     * @brief // Set Member Name <BR>
     * iStat = oPGisTableMember.setMemberName(value);
     *
     * @param value [in] value
     */
     // ----------------------------------------------------------------------------
     void setMemberName(const std::string &value);
     //==============================================================================
     /**
     * @brief // Get Member Type <BR>
     * iStat = oPGisTableMember.getMemberType();
     *
     * @return value
     */
     // ----------------------------------------------------------------------------
     std::string getMemberType() const;
     //==============================================================================
     /**
     * @brief // Set Member Type <BR>
     * iStat = oPGisTableMember.setMemberType(value);
     *
     * @param value [in] value
     */
     // ----------------------------------------------------------------------------
     void setMemberType(const std::string &value);
     //==============================================================================
     /**
     * @brief // Get Member Value <BR>
     * iStat = oPGisTableMember.getMemberValue();
     *
     * @return value
     */
     // ----------------------------------------------------------------------------
     std::string getMemberValue() const;
     //==============================================================================
     /**
     * @brief // Set Member Value <BR>
     * iStat = oPGisTableMember.setMemberValue(value);
     *
     * @param value [in] value
     */
     // ----------------------------------------------------------------------------
     void setMemberValue(const std::string &value);
     //==============================================================================

private:  // Private functions
     std::string MemberName;        /**< Name of Table Member */
  std::string MemberType;        /**< Type of Table Member */
  std::string MemberValue;       /**< String Value of Table Member */
};
//==============================================================================
/**
* @brief Definition Class sstPGisSampleBaseCls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstPGisSampleBaseCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor <BR>
  * iStat = oTest =  Func_1( iKey);
  *
  * @param poSqlFile [in] For the moment 0
  * @param oTabNam   [in] For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
     sstPGisSampleBaseCls(sstMisc01AscFilCls *poSqlFile, const std::string oTabNam);   // Constructor
   //  ~X();   // Destructor
     //==============================================================================
     /**
     * @brief // Set Table Member <BR>
     * iStat = oPGisSample.setTableMember ( iKey, oMemberName, oMemberType);
     *
     * @param iKey [in] For the moment 0
     * @param oMemberName [in] For the moment 0
     * @param oMemberType [in] For the moment 0
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetTableMember(int iKey,const std::string oMemberName, const std::string oMemberType);
     //==============================================================================
     /**
     * @brief // Set Value to Table Member <BR>
     * iStat = oPGisSample.setTableValue ( iRecNo, oMemberValue);
     *
     * @param iRecNo [in] Recond Number of Table member
     * @param oMemberValue [in] Value of Table member
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetTableValue(int iRecNo, const std::string oMemberValue);
     //==============================================================================
     /**
     * @brief // Set Value to Table Member <BR>
     * iStat = oPGisSample.setTableValue ( iRecNo, oMemberValue);
     *
     * @param iRecNo [in] Recond Number of Table member
     * @param iMemberValue [in] Value of Table member
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SetTableValueInt2(int iRecNo, const int iMemberValue);
     //==============================================================================
     /**
     * @brief // Get Value <BR>
     * iStat = oSampleBase.getEPSG();
     *
     * @return value
     */
     // ----------------------------------------------------------------------------
    std::string getEPSG() const;
    //==============================================================================
    /**
    * @brief // Set Value <BR>
    * iStat = oSampleBase.setEPSG(value);
    *
    * @param value [in] value
    */
    // ----------------------------------------------------------------------------
    void setEPSG(const std::string &value);
    //==============================================================================
    /**
    * @brief // Get Value <BR>
    * iStat = oSampleBase.getEPSG();
    *
    * @return value
    */
    // ----------------------------------------------------------------------------
    std::string getTabNam() const;
    //==============================================================================
    /**
    * @brief // Set Value <BR>
    * iStat = oSampleBase.setEPSG(value);
    *
    * @param value [in] value
    */
    // ----------------------------------------------------------------------------
    void setTabNam(const std::string &value);
    //==============================================================================
    /**
    * @brief // Start Row String with Insert-Statement and add GID Value <BR>
    * iStat = oSampleBase.SqlSampleRowInsertStartGID( ulGID);
    *
    * Writes something like this into String Row:
    * INSERT INTO TabNam (Name1) VALUES ( 0,
    *
    * @param ulGID [in] write ulGID to Row if not 0
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int SqlSampleRowInsertStartGID ( unsigned long ulGID);
    //==============================================================================
    /**
    * @brief // Add string value to Row String <BR>
    * iStat = oSampleBase.SqlSampleRowInsertString( oValStr);
    *
    * @param oValStr [in] oValStr
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int SqlSampleRowInsertString( const std::string oValStr);
    //==============================================================================
    /**
    * @brief // Add unsigned long int value to Row String <BR>
    * iStat = oSampleBase.SqlSampleRowInsertUnsignedLong( ulVal);
    *
    * @param ulVal [in] unsigned long int value
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int SqlSampleRowInsertUnsignedLong(const unsigned long ulVal);
    //==============================================================================
    /**
    * @brief // Add double value to Row String <BR>
    * iStat = oSampleBase.SqlSampleRowInsertDouble( dValStr);
    *
    * @param dValStr [in] dValStr
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int SqlSampleRowInsertDouble( const double dValStr);
    //==============================================================================
    /**
    * @brief // Write Drop Table Row to sql file <BR>
    * iStat = oSampleBase.SqlSampleRowDropTable ();
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int SqlSampleRowDropTable();

    //==============================================================================
    /**
    * @brief // Write Trucate Table Row to sql file <BR>
    * iStat = oSampleBase.SqlSampleRowTruncTable ();
    *
    * @return Errorstate
    *
    * @retval   = 0: OK
    * @retval   < 0: Unspecified Error
    */
    // ----------------------------------------------------------------------------
    int SqlSampleRowTruncTable();
    //==============================================================================
    /**
    * @brief // Get Value <BR>
    * iStat = oSampleBase.getSqlStr();
    *
    * @return value
    */
    // ----------------------------------------------------------------------------
    std::string getSqlStr() const;
    //==============================================================================
    /**
    * @brief // Set Value <BR>
    * iStat = oSampleBase.setSqlStr(value);
    *
    * @param value [in] value
    */
    // ----------------------------------------------------------------------------
    void setSqlStr(const std::string &value);

    sstMisc01AscFilCls  *poSqlFile;  /**< Name of sql file */
    std::vector<sstPGisTableMemberCls> oTableMemberVector;/**< Vector of Table Members */

protected:
    std::string oSqlStr;          /**< String Row for writing to SQL File */
    std::string oStatementStr;    /**< Sql statement row */
    unsigned int uiActTabRec;  /**< Actual Table Record */
private:  // Private functions
    std::string EPSG;        /**< EPSG Code as string */
    std::string oTabNam;     /**< Name of Table */


};
//==============================================================================
/**
* @brief Definition Class sstPGisSampleStringCls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstPGisSampleStringCls: public sstPGisSampleBaseCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor <BR>
  * iStat = oTest =  Func_1( iKey);
  *
  * @param poSqlFile [in] For the moment 0
  * @param oTabNam   [in] For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
     sstPGisSampleStringCls(sstMisc01AscFilCls *poSqlFile, const std::string oTabNam);   // Constructor
   //  ~X();   // Destructor
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Create Row and write to sql file <BR>
     * iStat = oSampleString.SqlSampleRowCreateTable();
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowCreateTable();
     //==============================================================================
     /**
     * @brief // write Row String to SQL File <BR>
     * iStat = oSampleString.SqlSampleRowInsertPointEnd( oPnt);
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowInsertEnd();
     //==============================================================================


// ----------------------------------------------------------------------------
  private:  // Private functions
  // int Dum;        /**< Dummy */
};
//==============================================================================
/**
* @brief Definition Class sstPGisSamplePointCls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstPGisSamplePointCls: public sstPGisSampleBaseCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor <BR>
  * iStat = oTest =  Func_1( iKey);
  *
  * @param poSqlFile [in] For the moment 0
  * @param oTabNam   [in] For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
     sstPGisSamplePointCls(sstMisc01AscFilCls *poSqlFile, const std::string oTabNam);   // Constructor
   //  ~X();   // Destructor
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Point Create Row and write to sql file <BR>
     * iStat = oSamplePoint.SqlSampleRowCreatePoint();
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowCreatePoint();
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Point Insert Row and write to sql file <BR>
     * iStat = oSamplePoint.SqlSampleRowInsertPoint(ulVal, oValStr, oPnt);
     *
     * For example value for tab member 1, value for tab member 2 and so on ..<BR>
     * iStat = oSamplePoint.SqlSampleRowInsertPoint( 1, "8100000000000", dPnt);  <BR>
     *
     * @param ulVal   [in] Value for Table member 1
     * @param oValStr [in] Value for Table Member 2
     * @param oPnt    [in] D3 Point
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowInsertPoint(unsigned long ulVal, const std::string oValStr,
                                 sstMath01dPnt3Cls oPnt);
     //==============================================================================
     /**
     * @brief // Add Point and EPSG value to row String and write Row String to SQL File <BR>
     * iStat = oSamplePoint.SqlSampleRowInsertPointEnd( oPnt);
     *
     *
     * @param oPnt    [in] D3 Point
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowInsertPointEnd(sstMath01dPnt3Cls oPnt);
     //==============================================================================


// ----------------------------------------------------------------------------
  private:  // Private functions
  // int Dum;        /**< Dummy */
};
//==============================================================================
/**
* @brief Definition Class sstPGisSampleLinestringCls
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstPGisSampleLinestringCls: public sstPGisSampleBaseCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor <BR>
  * iStat = oTest =  Func_1( iKey);
  *
  * @param poSqlFile [in] For the moment 0
  * @param oTabNam   [in] For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
     sstPGisSampleLinestringCls(sstMisc01AscFilCls *poSqlFile, const std::string oTabNam);   // Constructor
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Linestring Create Row and write to sql file <BR>
     * iStat = oSampleLinestring.SqlSampleRowCreateLinestring();
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowCreateLinestring();
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Linestring Insert Rows and write to sql file <BR>
     * iStat = oSampleLinestring.SqlSampleRowInsertLinestring(ulVal, oValStr, oPnt);
     *
     * @param ulVal       [in] Long Int Value for Table member 1
     * @param oValStr     [in] String Value for Table Member 2
     * @param poPntVector [in] D3 Point Vector for Linestring
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowInsertLinestring(unsigned long ulVal, const std::string oValStr,
                                 std::vector<sstMath01dPnt3Cls> *poPntVector);

   //  ~X();   // Destructor
  private:  // Private functions
  // int Dum;        /**< Dummy */
  // std::vector<sstMath01dPnt3Cls> oPntVector;
};
//==============================================================================
/**
* @brief Class creating Postgis Polygon (Area) objects
*
* More Comment
*
* Changed: 19.02.10  Re.
*
* @ingroup sstPostgis01Lib
*
* @author Re.
*
* @date 19.02.10
*/
// ----------------------------------------------------------------------------
class sstPGisSamplePolygonCls: public sstPGisSampleBaseCls
{
  public:   // Public functions
  //==============================================================================
  /**
  * @brief // Constructor <BR>
  * iStat = oTest =  Func_1( iKey);
  *
  * @param poSqlFile [in] For the moment 0
  * @param oTabNam   [in] For the moment 0
  *
  * @return Errorstate
  *
  * @retval   = 0: OK
  * @retval   < 0: Unspecified Error
  */
  // ----------------------------------------------------------------------------
     sstPGisSamplePolygonCls(sstMisc01AscFilCls *poSqlFile, const std::string oTabNam);   // Constructor
   //  ~X();   // Destructor
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Polygon Create Row and write to sql file <BR>
     * iStat = oSamplePolygon.SqlSampleRowCreatePolygon();
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowCreatePolygon();
     //==============================================================================
     /**
     * @brief // Sample Data in Sql Polygon (Arae)Insert Rows and write to sql file <BR>
     * iStat = oSamplePolygon.SqlSampleRowInsertPolygon(ulVal, oValStr, oPnt);
     *
     * @param ulVal       [in] Long Int Value for Table member 1 (for example GID)
     * @param oValStr     [in] String Value for Table Member 2 (for example DBS)
     * @param poPntVector [in] D3 Point Vector for Linestring
     *
     * @return Errorstate
     *
     * @retval   = 0: OK
     * @retval   < 0: Unspecified Error
     */
     // ----------------------------------------------------------------------------
     int SqlSampleRowInsertPolygon(unsigned long ulVal, const std::string oValStr,
                                 std::vector<sstMath01dPnt3Cls> *poPntVector);

//==============================================================================
/**
* @brief // Shortstory <BR>
* iStat = oTest =  Func_1( iKey);
*
* @param iKey [in] For the moment 0
*
* @return Errorstate
*
* @retval   = 0: OK
* @retval   < 0: Unspecified Error
*/
// ----------------------------------------------------------------------------
   //  Func_1(int iKey);
// ----------------------------------------------------------------------------
  // int Dum2;       /**< Dummy2 */
  private:  // Private functions
  int Dum;        /**< Dummy */
};
//-----------------------------------------------------------------------------


#endif

// ------------------------------------------------------------------- Ende ----


