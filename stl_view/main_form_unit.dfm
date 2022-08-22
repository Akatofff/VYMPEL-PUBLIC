object main_form: Tmain_form
  Left = 385
  Top = 181
  Width = 625
  Height = 671
  Caption = 'stl view'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCloseQuery = FormCloseQuery
  OnMouseWheelDown = FormMouseWheelDown
  OnMouseWheelUp = FormMouseWheelUp
  DesignSize = (
    617
    617)
  PixelsPerInch = 96
  TextHeight = 13
  object Shape: TShape
    Left = 8
    Top = 8
    Width = 601
    Height = 601
    Anchors = [akLeft, akTop, akRight, akBottom]
    Pen.Color = clGray
  end
  object MainMenu1: TMainMenu
    Left = 16
    Top = 16
    object file_itm: TMenuItem
      Caption = #1060#1072#1081#1083
      object open_itm: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100'...'
        OnClick = open_itmClick
      end
    end
    object view_itm: TMenuItem
      Caption = #1042#1080#1076
      object basis_itm: TMenuItem
        Caption = #1041#1072#1079#1080#1089
        Checked = True
        OnClick = c_itmClick
      end
      object ext_view_itm: TMenuItem
        Caption = #1044#1086#1087#1086#1083#1085#1080#1090#1077#1083#1100#1085#1099#1077' '#1074#1080#1076#1099
        OnClick = x_view_itmClick
      end
      object wire_itm: TMenuItem
        Caption = #1050#1072#1088#1082#1072#1089
        OnClick = c_itmClick
      end
      object go_to_default_pos_itm: TMenuItem
        Caption = #1042#1086#1079#1074#1088#1072#1090' '#1074' '#1087#1086#1079#1080#1094#1080#1102' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
        OnClick = go_to_default_pos_itmClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object options_itm: TMenuItem
        Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072'...'
        OnClick = options_itmClick
      end
    end
    object help_itm: TMenuItem
      Caption = #1055#1086#1084#1086#1097#1100
      object show_help_itm: TMenuItem
        Caption = #1057#1087#1088#1072#1074#1082#1072'...'
        ShortCut = 112
        OnClick = show_help_itmClick
      end
      object about_itm: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
        OnClick = about_itmClick
      end
    end
  end
  object OpenDialog: TOpenDialog
    Filter = 'STL txt|*.stl|STL bin|*.stl|OBJ|*.obj'
    Left = 48
    Top = 16
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    Left = 80
    Top = 16
  end
end
