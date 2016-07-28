object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 499
  ClientWidth = 616
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 32
    Top = 32
    Width = 545
    Height = 337
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object TCPServer: TIdTCPServer
    Bindings = <
      item
        IP = '127.0.0.1'
        Port = 7010
      end>
    DefaultPort = 7010
    OnExecute = TCPServerExecute
    Left = 304
    Top = 256
  end
end
