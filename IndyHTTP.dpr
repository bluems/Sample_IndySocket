program IndyHTTP;

uses
  System.StartUpCopy,
  FMX.Forms,
  uIDHTTP in 'uIDHTTP.pas' {Form3};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm3, Form3);
  Application.Run;
end.
