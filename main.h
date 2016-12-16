//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <System.Bluetooth.Components.hpp>
#include <System.Bluetooth.hpp>
#include <FMX.Edit.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
	TBluetooth *Bluetooth1;
	TButton *ConnectBtn;
	TMemo *LogMemo;
	TComboBox *PairedDevicesList;
	TTimer *Timer1;
	TLabel *Label1;
	TButton *SendBtn;
	TEdit *CommandEdit;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ConnectBtnClick(TObject *Sender);
	void __fastcall SendBtnClick(TObject *Sender);
private:	// Benutzer-Deklarationen
public:		// Benutzer-Deklarationen
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
