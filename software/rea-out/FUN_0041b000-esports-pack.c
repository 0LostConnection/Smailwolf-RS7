// 0041b000

undefined4 __fastcall FUN_0041b000(int param_1)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int unaff_EDI;
  undefined2 *puVar5;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00534484;
  local_10 = ExceptionList;
  uVar2 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  piVar3 = (int *)FUN_00406b10();
  if (piVar3 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00406bc0(0x80004005);
  }
  local_14 = (**(code **)(*piVar3 + 0xc))();
  local_14 = local_14 + 0x10;
  local_8 = 0;
  iVar4 = YJXUI::CRadioButton::GetCheck(*(CRadioButton **)(param_1 + 0x470));
  if (iVar4 == 0) {
    puVar5 = &DAT_0054a528;
  }
  else {
    puVar5 = &DAT_0054a480;
  }
  FUN_00405eb0(&local_14,puVar5,1);
  iVar4 = local_14;
  piVar3 = (int *)(local_14 + -0x10);
  FUN_00405df0(piVar3);
  local_8._0_1_ = 1;
  FUN_004054f0(&stack0xffffffcc,L"scroll_flag");
  local_8._0_1_ = 2;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 3;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 2;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00401860(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),uVar2,unaff_EDI);
  local_8 = 0xffffffff;
  LOCK();
  piVar1 = (int *)(iVar4 + -4);
  iVar4 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar4 == 1 || iVar4 + -1 < 0) {
    (**(code **)(*(int *)*piVar3 + 4))();
  }
  ExceptionList = local_10;
  return 1;
}

