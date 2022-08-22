object about_form: Tabout_form
  Left = 192
  Top = 114
  BorderStyle = bsToolWindow
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 138
  ClientWidth = 289
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnShortCut = FormShortCut
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 273
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1076#1083#1103' '#1087#1088#1086#1089#1084#1086#1090#1088#1072' STL-'#1092#1072#1081#1083#1086#1074
  end
  object Label2: TLabel
    Left = 8
    Top = 32
    Width = 273
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = #1040#1074#1090#1086#1088': '#1043#1091#1089#1077#1074' '#1040'. '#1055'.'
  end
  object ok: TButton
    Left = 112
    Top = 104
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
    OnClick = okClick
  end
end
