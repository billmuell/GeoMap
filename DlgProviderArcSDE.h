#pragma once

#include "resource.h"

// Cuadro de diálogo de DlgProviderArcSDE

class DlgProviderArcSDE : public CDialog
{
	DECLARE_DYNAMIC(DlgProviderArcSDE)

public:
	DlgProviderArcSDE(CWnd* pParent = NULL);   // Constructor estándar
	virtual ~DlgProviderArcSDE();

// Datos del cuadro de diálogo
	enum { IDD = IDD_DLG_PROV_SDE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

	DECLARE_MESSAGE_MAP()
};
