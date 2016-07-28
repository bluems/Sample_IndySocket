unit Userver;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, IdBaseComponent, IdComponent,
  IdTCPConnection, IdTCPClient, Vcl.StdCtrls, IdCustomTCPServer, IdTCPServer,IdContext;

type
  TForm1 = class(TForm)
    TCPServer: TIdTCPServer;
    Memo1: TMemo;
    procedure TCPServerExecute(AContext:TIdContext);
    procedure FormCreate(Sender:TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}


procedure TForm1.FormCreate(Sender: TObject);
begin
  TCPServer.Active:= True;
  Memo1.Text:='Server START!'+#13#10;
end;

procedure TForm1.TCPServerExecute(AContext: TIdContext);
var
  {ip:String;
  guid:String;
  State:String;
  Amp:String;}
  packet:string;
begin
  with AContext.Connection do
  begin
    {ip:=Socket.ReadLn;
    guid:=Socket.ReadLn;
    State:=Socket.ReadLn;
    Amp:=Socket.ReadLn;}
    packet:=socket.ReadLn;
    Memo1.text:=Memo1.Text+{'ip : '+ip+', guid : '+guid+', state : '+state+', amp : '+amp+#13#10;}
                  packet+#13#10;
    //   Memo1.Text:=Memo1.Text+'Message : '+ip;
    Socket.WriteLnRFC(copy(packet,9,ByteToCharLen(packet,length(packet))-9));
    Disconnect;
  end;
end;

end.
