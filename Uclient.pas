unit Uclient;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient;

type
  TForm2 = class(TForm)
    TCPClient: TIdTCPClient;
    Panel1: TPanel;
    Button1: TButton;
    Memo1: TMemo;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

{$R *.dfm}

procedure TForm2.Button1Click(Sender: TObject);
begin
  with TCPClient do
  begin
    Connect;
    try

      TCPClient.Socket.WriteLn('Hello');
      TCPClient.Socket.WriteLn('{FE43E8F1-180F-46E8-880E-4A96914F13F8}');
      TCPClient.Socket.WriteLn('1');
      TcpClient.Socket.WriteLn('70');
      Memo1.Text:=Memo1.Text+TCPClient.Socket.Readln+#13#10;
      Disconnect;
    finally
      Disconnect;
    end;
  end;
end;

end.
