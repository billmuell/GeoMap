#pragma once

class CCadEntity
{
protected:
  AcDbEntity * _entity;
public:
  CCadEntity(AcDbEntity * entity);
public:
  ~CCadEntity(void);
public:
  CCadEntity(const CCadEntity & entity);
public:
  void Draw();
};
