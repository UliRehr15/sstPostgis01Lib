# sstPostgis01Lib
sstPostgis01Lib - C++ Library for creating Postgis Sql import statements in file

Class for creating POINT objects import statements. <BR>
Class for creating LINESTRING objects import statements. <BR>

This Library is created with QtCreator 4.14.1, Qt 5.15.2  and gcc 9.0.0. <BR>

-------------------------------------------------------------------------------

App sstPostgis01LibTest creates new SQL-File with test data contents something like this: <BR>

CREATE TABLE Form ( gid serial primary key, DBS varchar(20), geom geometry(POINT) ); <BR>
INSERT INTO Form (gid,DBS,geom) VALUES ( 1,'8100000000000',ST_GeomFromText('POINT(32539500.00 5802600.00)' ,3456)  ); <BR>
CREATE TABLE LA ( gid serial primary key, DBS varchar(20), geom geometry(LINESTRING) ); <BR>
INSERT INTO LA ( gid, DBS, geom) VALUES ( 1,'8100000000000',ST_GeomFromText('LINESTRING( <BR>
32539500.00 5802600.00,  <BR>
32539600.00 5802500.00,  <BR>
32539700.00 5802400.00  <BR>
)' ,3456)  );  <BR>

This file could be imported to PostgreSQL/Postgis via PgAdmin4 > Import SQL-File. <BR>
-------------------------------------------------------------------------------
App sstDxf2Postgis01 imports Dxf Data to Postgis Import SQL-File


-------------------------------------------------------------------------------
Structure of coding projects should be:

.. [libs] <BR>
   [sstMath01Lib] <BR>
   [sstStr01Lib] <BR>
   [sstMisc01Lib] <BR>
   [sstRec04Lib] <BR>
   [Doxygen_Output] <BR>

July 2021, Hanover, Germany, Uli Rehr

Versions <BR>

20210722: Version 1.00: Create empty repo in github. <BR>
20210928: Version 1.01: Test update repo. <BR>
20210929: Version 1.02: Add Code to repo. <BR>
20210930: Version 1.03: Add Test App sstPostgis01LibTest. <BR>
20211008: Version 1.04: Add Test App sstDxf2Postgis01. <BR>
