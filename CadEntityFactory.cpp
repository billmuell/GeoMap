#include "stdafx.h"
#include "CadEntityFactory.h"

#include "CadEntity.h"
#include "CadLine.h"
#include "CadPoint.h"
#include "CadPolygon.h"

CCadEntityFactory::CCadEntityFactory(void)
{
}

CCadEntityFactory::~CCadEntityFactory(void)
{
}

CCadEntity * CCadEntityFactory::GetCadEntity(FdoPtr<FdoIGeometry> geom) 
{
  FdoGeometryType type = geom->GetDerivedType();
	
  switch (type) {
    case FdoGeometryType_Point:
#ifdef LOG
      acutPrintf(L"FdoGeometryType_Point\n");
#endif
      return (CCadEntity *)new CCadPoint(static_cast<FdoIPoint*>(geom.p));
      //return 0;

    case FdoGeometryType_MultiPoint:
#ifdef LOG
      acutPrintf(L"FdoGeometryType_MultiPoint\n");
#endif
      return (CCadEntity *)new CCadPoint(static_cast<FdoIMultiPoint*>(geom.p));
      //return 0;

    case FdoGeometryType_LineString:
#ifdef LOG
      acutPrintf(L"FdoGeometryType_LineString\n");
#endif
      return (CCadEntity *)new CCadLine(static_cast<FdoILineString*>(geom.p));
      
    case FdoGeometryType_MultiLineString:
#ifdef LOG
			acutPrintf(L"FdoGeometryType_MultiLineString\n");
#endif
      return (CCadEntity *)new CCadLine(static_cast<FdoIMultiLineString*>(geom.p));
      
    case FdoGeometryType_Polygon:
#ifdef LOG
			acutPrintf(L"FdoGeometryType_Polygon\n");
#endif
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));

    case FdoGeometryType_MultiPolygon:
#ifdef LOG
			acutPrintf(L"FdoGeometryType_MultiPolygon\n");
#endif
      return (CCadEntity *)new CCadPolygon(static_cast<FdoIMultiPolygon*>(geom.p));

    case FdoGeometryType_CurveString:
#ifdef LOG
#endif
			acutPrintf(L"FdoGeometryType_CurveString\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;

    case FdoGeometryType_CurvePolygon:
#ifdef LOG
#endif
			acutPrintf(L"FdoGeometryType_CurvePolygon\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;

    case FdoGeometryType_MultiCurveString:
#ifdef LOG
#endif
			acutPrintf(L"FdoGeometryType_MultiCurveString\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;

    case FdoGeometryType_MultiCurvePolygon:
#ifdef LOG
#endif
			acutPrintf(L"FdoGeometryType_MultiCurvePolygon\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;
      
    case FdoGeometryType_MultiGeometry:
#ifdef LOG
#endif
			acutPrintf(L"FdoGeometryType_MultiGeometry\n");
      //return (CCadEntity *)new CCadPolygon(static_cast<FdoIPolygon*>(geom.p));
      return 0;
      
    case FdoGeometryType_None:
#ifdef LOG
#endif
      acutPrintf(L"FdoGeometryType_None\n");
      return 0;

    default:
#ifdef LOG
#endif
			acutPrintf(L"FdoGeometryType_Unexpected\n");
      return 0;
	}
}

CCadEntity * CCadEntityFactory::GetCadEntity(AcDbObjectId & idEntity)
{
  AcDbEntity * entity = 0;
  if (acdbOpenObject(entity, idEntity, AcDb::kForRead) != Acad::eOk) return 0;
  
  CCadEntity * cadEntity = CCadEntityFactory::GetCadEntity(entity);
  entity->close();
  
  return cadEntity;
}

CCadEntity * CCadEntityFactory::GetCadEntity(AcDbEntity * entity)
{
  CCadEntity * cadEntity = 0;
  if (entity->isKindOf(AcDbPoint::desc()) ||
    entity->isKindOf(AcDbText::desc()) ||
    entity->isKindOf(AcDbMText::desc()) ||
    entity->isKindOf(AcDbBlockReference::desc())) {
    
      cadEntity = new CCadPoint(entity);
  
  } else if (entity->isKindOf(AcDbLine::desc()) ||
      entity->isKindOf(AcDbArc::desc()) ||
      entity->isKindOf(AcDbSpline::desc())) {
        
        cadEntity = new CCadLine(entity);
  
  } else if (entity->isKindOf(AcDbEllipse::desc()) ||
    entity->isKindOf(AcDbCircle::desc())) {
      cadEntity = new CCadPolygon(entity);
  
  } else if (entity->isKindOf(AcDb2dPolyline::desc())) {
    
    AcDb2dPolyline * e = AcDb2dPolyline::cast(entity);
    if (e->isClosed()) cadEntity = new CCadPolygon(entity);
    else cadEntity = new CCadLine(entity);
    
  } else if (entity->isKindOf(AcDbPolyline::desc())) {
    
    AcDbPolyline * e = AcDbPolyline::cast(entity);
    if (e->isClosed()) cadEntity = new CCadPolygon(entity);
    else cadEntity = new CCadLine(entity);
  }
  
  resbuf * data = entity->xData(APPNAME);
  if (data != NULL) cadEntity->SetData(CFeatureData(data->rbnext->resval.rstring));
  acutRelRb(data);
  
  return cadEntity;
}