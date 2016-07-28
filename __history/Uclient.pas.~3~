unit Uclient;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls, Vcl.ExtCtrls,
  IdBaseComponent, IdComponent, IdTCPConnection, IdTCPClient;

type
  TForm2 = class(TForm)
    TCPClient: TIdTCPClient;
    ListBox1: TListBox;
    Panel1: TPanel;
    Button1: TButton;
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

      TCPClient.Socket.WriteLnRFC('Hello');
      TCPClient.Socket.WriteLnRFC('{FE43E8F1-180F-46E8-880E-4A96914F13F8}');
      TCPClient.Socket.WriteLnRFC('1');
      TcpClient.Socket.WriteLnRFC('70');
      ListBox1.Items.Add(TCPClient.Socket.Readln);
      Disconnect;
    finally
      Disconnect;
    end;
  end;
end;

end.
