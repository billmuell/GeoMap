#pragma once

#include "resource.h"

// Cuadro de di�logo de DlgProviderArcSDE

class DlgProviderArcSDE : public CDialog
{
	DECLARE_DYNAMIC(DlgProviderArcSDE)

public:
	DlgProviderArcSDE(CWnd* pParent = NULL);   // Constructor est�ndar
	virtual ~DlgProviderArcSDE();

// Datos del cuadro de di�logo
	enum { IDD = IDD_DLG_PROV_SDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
};
