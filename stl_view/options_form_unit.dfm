object options_form: Toptions_form
  Left = 190
  Top = 114
  BorderStyle = bsToolWindow
  Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
  ClientHeight = 297
  ClientWidth = 185
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
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 23
    Height = 13
    Caption = #1060#1086#1085
  end
  object Label2: TLabel
    Left = 8
    Top = 56
    Width = 134
    Height = 13
    Caption = #1054#1089#1074#1077#1097#1077#1085#1080#1077' '#1085#1072#1087#1088#1072#1074#1083#1077#1085#1085#1086#1077
  end
  object Label3: TLabel
    Left = 8
    Top = 80
    Width = 5
    Height = 13
    Caption = 'x'
  end
  object Label4: TLabel
    Left = 8
    Top = 104
    Width = 5
    Height = 13
    Caption = 'y'
  end
  object Label5: TLabel
    Left = 8
    Top = 128
    Width = 5
    Height = 13
    Caption = 'z'
  end
  object Label6: TLabel
    Left = 8
    Top = 32
    Width = 122
    Height = 13
    Caption = #1054#1089#1074#1077#1097#1077#1085#1080#1077' '#1088#1072#1089#1089#1077#1103#1085#1085#1086#1077
  end
  object Label7: TLabel
    Left = 8
    Top = 160
    Width = 30
    Height = 13
    Caption = #1057#1076#1074#1080#1075
  end
  object Label8: TLabel
    Left = 8
    Top = 184
    Width = 5
    Height = 13
    Caption = 'x'
  end
  object Label9: TLabel
    Left = 8
    Top = 208
    Width = 5
    Height = 13
    Caption = 'y'
  end
  object Label10: TLabel
    Left = 8
    Top = 232
    Width = 5
    Height = 13
    Caption = 'z'
  end
  object bg_color: TPanel
    Left = 160
    Top = 8
    Width = 17
    Height = 17
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 0
    OnClick = bg_colorClick
  end
  object LightPosition_x: TEdit
    Left = 56
    Top = 80
    Width = 121
    Height = 21
    TabOrder = 3
    OnChange = LightPosition_xChange
  end
  object LightPosition_y: TEdit
    Left = 56
    Top = 104
    Width = 121
    Height = 21
    TabOrder = 4
    OnChange = LightPosition_xChange
  end
  object LightPosition_z: TEdit
    Left = 56
    Top = 128
    Width = 121
    Height = 21
    TabOrder = 5
    OnChange = LightPosition_xChange
  end
  object ok: TButton
    Left = 16
    Top = 264
    Width = 75
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 9
    OnClick = okClick
  end
  object cancel: TButton
    Left = 96
    Top = 264
    Width = 75
    Height = 25
    Caption = #1042#1099#1081#1090#1080
    ModalResult = 2
    TabOrder = 10
    OnClick = cancelClick
  end
  object LightAmbient_color: TPanel
    Left = 160
    Top = 32
    Width = 17
    Height = 17
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    ParentShowHint = False
    ShowHint = False
    TabOrder = 1
    OnClick = bg_colorClick
  end
  object LightDiffuse_color: TPanel
    Left = 160
    Top = 56
    Width = 17
    Height = 17
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    ParentShowHint = False
    ShowHint = False
    TabOrder = 2
    OnClick = bg_colorClick
  end
  object d_x: TEdit
    Left = 56
    Top = 184
    Width = 121
    Height = 21
    TabOrder = 6
    Text = '0'
    OnChange = LightPosition_xChange
  end
  object d_y: TEdit
    Left = 56
    Top = 208
    Width = 121
    Height = 21
    TabOrder = 7
    Text = '0'
    OnChange = LightPosition_xChange
  end
  object d_z: TEdit
    Left = 56
    Top = 232
    Width = 121
    Height = 21
    TabOrder = 8
    Text = '0'
    OnChange = LightPosition_xChange
  end
end
