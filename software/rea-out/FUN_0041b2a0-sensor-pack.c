// 0041b2a0

undefined4 __fastcall FUN_0041b2a0(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int unaff_EDI;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00534cc4;
  local_10 = ExceptionList;
  uVar3 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  YJXUI::CCheckButton::GetCheck(*(CCheckButton **)(param_1 + 0x458));
  YJXUI::CCheckButton::GetCheck(*(CCheckButton **)(param_1 + 0x45c));
  YJXUI::CCheckButton::GetCheck(*(CCheckButton **)(param_1 + 0x460));
  piVar4 = (int *)FUN_00406b10();
  if (piVar4 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00406bc0(0x80004005);
  }
  local_14 = (**(code **)(*piVar4 + 0xc))();
  local_14 = local_14 + 0x10;
  local_8 = 0;
  FUN_00406540(&local_14,0x54a358);
  iVar2 = local_14;
  piVar4 = (int *)(local_14 + -0x10);
  FUN_00405df0(piVar4);
  local_8._0_1_ = 1;
  FUN_004054f0(&stack0xffffffc8,L"sensor_flag");
  local_8._0_1_ = 2;
  if ((*(int *)(*(int *)ThreadLocalStoragePointer + 4) < DAT_0056ef90) &&
     (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
    local_8._0_1_ = 3;
    FUN_00401290();
    _atexit(thunk_FUN_004013b0);
    local_8._0_1_ = 2;
    FUN_00448621(&DAT_0056ef90);
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00401860(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),uVar3,unaff_EDI);
  local_8 = 0xffffffff;
  LOCK();
  piVar1 = (int *)(iVar2 + -4);
  iVar2 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar2 == 1 || iVar2 + -1 < 0) {
    (**(code **)(*(int *)*piVar4 + 4))();
  }
  ExceptionList = local_10;
  return 1;
}

