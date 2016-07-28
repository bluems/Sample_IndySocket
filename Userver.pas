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
  hello, guid, bool, num:string;
begin
  with AContext.Connection do
  begin
    hello:=socket.ReadLn;
    guid:=socket.ReadLn;
    bool:=socket.ReadLn;
    num:=socket.ReadLn;
    memo1.Lines.Append(hello+guid+bool+num);
    //Memo1.text:=Memo1.Text+;
    //   Memo1.Text:=Memo1.Text+'Message : '+ip;
    Socket.WriteLn(copy(guid,11,ByteToCharLen(guid,length(guid))-11));
    Disconnect;
  end;
end;

end.
