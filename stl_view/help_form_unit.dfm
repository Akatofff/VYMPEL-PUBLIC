object help_form: Thelp_form
  Left = 192
  Top = 114
  BorderStyle = bsToolWindow
  Caption = #1055#1086#1084#1086#1097#1100
  ClientHeight = 137
  ClientWidth = 417
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
  object ok: TButton
    Left = 176
    Top = 104
    Width = 75
    Height = 25
    Caption = 'OK'
    ModalResult = 1
    TabOrder = 0
    OnClick = okClick
  end
  object Memo: TMemo
    Left = 8
    Top = 8
    Width = 401
    Height = 89
    Color = clBtnFace
    Lines.Strings = (
      #1044#1074#1080#1078#1077#1085#1080#1077' '#1089' '#1085#1072#1078#1072#1090#1099#1084' '#1050#1052' ('#1080#1083#1080' Shift+'#1051#1050#1052') - '#1087#1072#1085#1086#1088#1072#1084#1080#1088#1086#1074#1072#1085#1080#1077
      #1042#1088#1072#1097#1077#1085#1080#1077' '#1050#1052' - '#1079#1091#1084#1080#1088#1086#1074#1072#1085#1080#1077
      #1044#1074#1080#1078#1077#1085#1080#1077' '#1089' '#1085#1072#1078#1072#1090#1086#1081' '#1051#1050#1052' - '#1074#1088#1072#1097#1077#1085#1080#1077
      #1044#1074#1086#1081#1085#1086#1077' '#1085#1072#1078#1072#1090#1080#1077' '#1050#1052' - '#1074#1086#1079#1074#1088#1072#1090' '#1074' '#1087#1086#1079#1080#1094#1080#1102' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102)
    ReadOnly = True
    TabOrder = 1
  end
end
