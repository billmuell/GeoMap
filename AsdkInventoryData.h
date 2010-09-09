//
// (C) Copyright 1996,1998 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.

#ifndef ASDKINVENTORYDATA_H
#define ASDKINVENTORYDATA_H 1

// String used for command group name, and REGAPP name, and
// other places where a text key is required.
#define ED_INVENTORY_SERVICE  L"GEOMAP_DICT_ID"
#define ED_INVENTORY_GROUP  L"GEOMAP_DICT_GROUP"

/* ================ AsdkInventoryData ================ */

/* AsdkInventoryData

   This class stores and maintains a char string that ostensibly
   represents an Inventory identifier.  Could be anything, really.

   Intstances of this class are intended to be stored in object
   extension dictionaries, under the named defined in the literal
   ED_INVENTORY_SERVICE.

   Its two members are inventoryId() and setInventoryId(), which
   return a malloced string, and record a copy of an input string
   respectively.
*/

class AsdkInventoryData: public AcDbObject 
{ 
 
  public:
    ACRX_DECLARE_MEMBERS(AsdkInventoryData);

    // AsdkInventoryData protocol

    AsdkInventoryData();
    virtual ~AsdkInventoryData();

    ACHAR* inventoryId() const;

    void setInventoryId(const ACHAR* inventoryId);

    // Overridden methods from AcDbObject

    virtual Acad::ErrorStatus   dwgInFields(AcDbDwgFiler* filer);
    virtual Acad::ErrorStatus   dwgOutFields(AcDbDwgFiler* filer) const;

    virtual Acad::ErrorStatus   dxfInFields(AcDbDxfFiler* filer);
    virtual Acad::ErrorStatus   dxfOutFields(AcDbDxfFiler* filer) const;

  private:

    ACHAR* mId;
 
};

#endif // ASDKINVENTORYDATA_H