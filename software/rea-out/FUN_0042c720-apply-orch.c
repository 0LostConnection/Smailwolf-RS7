
void __fastcall FUN_0042c720(MDialog *param_1)

{
  int iVar1;
  int iVar2;
  undefined *this;
  undefined4 *this_00;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int unaff_ESI;
  int iVar3;
  int iVar4;
  char *pcVar5;
  undefined1 *puVar6;
  char local_94 [9];
  undefined2 local_8b;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0053668a;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00426000((int)param_1);
  FUN_00412630(param_1);
  *(undefined4 *)(param_1 + 0x6f4) = 0;
  FUN_00410ed0((int)param_1);
  FUN_004177f0(param_1);
  iVar1 = *(int *)ThreadLocalStoragePointer;
  if (*(int *)(iVar1 + 4) < DAT_0056ef18) {
    FUN_00448660(&DAT_0056ef18);
    if (DAT_0056ef18 == -1) {
      local_8 = 0;
      FUN_0043b7c0();
      _atexit(thunk_FUN_0043b8c0);
      local_8 = 0xffffffff;
      FUN_00448621(&DAT_0056ef18);
    }
  }
  iVar2 = FUN_0043bc50(0x56eef0);
  iVar4 = extraout_ECX;
  if (iVar2 == 0) {
    FUN_004054f0(&stack0xffffff5c,(short *)&DAT_0054a4d8);
    local_8 = 1;
    iVar2 = extraout_ECX_00;
    FUN_004054f0(&stack0xffffff58,L"report_rate");
    local_8 = CONCAT31(local_8._1_3_,2);
  }
  else {
    FUN_004054f0(&stack0xffffff5c,(short *)&DAT_0054a4d8);
    local_8 = 3;
    iVar2 = extraout_ECX_01;
    FUN_004054f0(&stack0xffffff58,L"report_rate");
    local_8 = CONCAT31(local_8._1_3_,4);
  }
  iVar3 = *(int *)(param_1 + 0x6f0);
  this = FUN_00401170();
  local_8 = 0xffffffff;
  FUN_00401860(this,iVar3,iVar2,iVar4);
  puVar6 = &stack0xffffff5c;
  FUN_004054f0(&stack0xffffff5c,&DAT_0054a480);
  local_8 = 5;
  FUN_004054f0(&stack0xffffff58,L"light_mode");
  local_8._0_1_ = 6;
  if (*(int *)(iVar1 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 7;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8 = CONCAT31(local_8._1_3_,6);
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8 = 0xffffffff;
  FUN_00401860(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),unaff_ESI,(int)puVar6);
  FUN_00418950(param_1);
  FUN_0042ac40();
  FUN_0042b470();
  FUN_0042ba10((int)param_1);
  FUN_004169a0((int)param_1);
  memset(local_94 + 1,0,0x7f);
  local_94[8] = (char)param_1[0x6f0] - 1;
  local_94[0] = '\0';
  local_94[1] = 'U';
  local_94[2] = '0';
  local_94[3] = -0x5b;
  pcVar5 = local_94;
  local_94[4] = '\v';
  local_94[5] = '.';
  local_94[6] = '\0';
  local_94[7] = '\0';
  local_8b = 0;
  this_00 = FUN_00401200();
  FUN_0043be10(this_00,pcVar5);
  if ((local_94[0] == -0x56) && (local_94[1] == '0')) {
    YJXUI::BatteryCtrl::SetBatteryInfo
              (*(BatteryCtrl **)(param_1 + 0x2f4),(uint)(byte)local_94[8],(uint)(byte)local_8b);
  }
  ExceptionList = local_10;
  local_94[4] = -0x6a;
  local_94[5] = -0x37;
  local_94[6] = 'B';
  local_94[7] = '\0';
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

