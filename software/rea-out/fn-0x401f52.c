void __thiscall FUN_00401b90(void *this,int param_1)

{
  int iVar1;
  int *piVar2;
  char ***pppcVar3;
  char *pcVar4;
  undefined4 *puVar5;
  uint uVar6;
  int local_a4;
  int local_a0;
  undefined4 local_9c [3];
  undefined4 local_90 [6];
  undefined4 local_78 [6];
  void *local_60 [4];
  undefined4 local_50;
  uint local_4c;
  char **local_48 [4];
  uint local_38;
  uint local_34;
  char **local_30 [4];
  uint local_20;
  uint local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00532853;
  local_10 = ExceptionList;
  local_18 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00447f90(local_9c);
  local_8 = 0;
  local_34 = 0xf;
  local_38 = 0;
  local_48[0] = (char **)((uint)local_48[0] & 0xffffff00);
  FUN_004056f0(local_48,(int *)"version",7);
  local_8._0_1_ = 1;
  local_1c = 0xf;
  local_20 = 0;
  local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
  FUN_004056f0(local_30,(int *)"1.0.1",5);
  local_8._0_1_ = 2;
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"light_mode",10);
  FUN_004056f0(local_30,(int *)&DAT_0054a2bc,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"sleep_light",0xb);
  FUN_004056f0(local_30,(int *)&DAT_0054a2cc,2);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  piVar2 = (int *)FUN_00406b10();
  if (piVar2 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00406bc0(0x80004005);
  }
  local_a0 = (**(code **)(*piVar2 + 0xc))();
  local_a0 = local_a0 + 0x10;
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_004056f0(local_48,(int *)"report_rate",0xb);
  FUN_004056f0(local_30,(int *)&DAT_0054a2dc,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"button_respondtime",0x12);
  if (*(int *)((int)this + 0x68) < 0xc9) {
    piVar2 = (int *)&DAT_0054a2f8;
  }
  else {
    piVar2 = (int *)&DAT_0054a2f4;
  }
  FUN_004056f0(local_30,piVar2,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"sensor_flag",0xb);
  FUN_004056f0(local_30,(int *)&DAT_0054a308,2);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"liftoff_height",0xe);
  FUN_004056f0(local_30,(int *)&DAT_0054a2bc,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"scroll_flag",0xb);
  FUN_004056f0(local_30,(int *)&DAT_0054a328,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"e-sports_flag",0xd);
  FUN_004056f0(local_30,(int *)&DAT_0054a2bc,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"leftbtn_lock",0xc);
  FUN_004056f0(local_30,(int *)&DAT_0054a2bc,1);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_flag",8);
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_index",9);
  atoi("2");
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_count",9);
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8._0_1_ = 3;
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group0_value",0x10);
  FUN_00405450(&local_a4,"800");
  local_8 = CONCAT31(local_8._1_3_,7);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a4);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_8._0_1_ = 3;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  LOCK();
  piVar2 = (int *)(local_a4 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_a4 + -0x10) + 4))((undefined4 *)(local_a4 + -0x10));
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group1_value",0x10);
  FUN_00405450(&local_a4,"1600");
  local_8 = CONCAT31(local_8._1_3_,9);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a4);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_8._0_1_ = 3;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  LOCK();
  piVar2 = (int *)(local_a4 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_a4 + -0x10) + 4))((undefined4 *)(local_a4 + -0x10));
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group2_value",0x10);
  FUN_00405450(&local_a4,"2400");
  local_8 = CONCAT31(local_8._1_3_,0xb);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a4);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_8._0_1_ = 3;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  LOCK();
  piVar2 = (int *)(local_a4 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_a4 + -0x10) + 4))((undefined4 *)(local_a4 + -0x10));
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group3_value",0x10);
  FUN_00405450(&local_a4,"3200");
  local_8 = CONCAT31(local_8._1_3_,0xd);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a4);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_8._0_1_ = 3;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  LOCK();
  piVar2 = (int *)(local_a4 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_a4 + -0x10) + 4))((undefined4 *)(local_a4 + -0x10));
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group4_value",0x10);
  FUN_00405450(&local_a4,"6400");
  local_8 = CONCAT31(local_8._1_3_,0xf);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a4);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_8._0_1_ = 3;
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  LOCK();
  piVar2 = (int *)(local_a4 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_a4 + -0x10) + 4))((undefined4 *)(local_a4 + -0x10));
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group5_value",0x10);
  FUN_00405450(&local_a4,"20000");
  local_8 = CONCAT31(local_8._1_3_,0x11);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a4);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  local_4c = 0xf;
  local_50 = 0;
  local_60[0] = (void *)((uint)local_60[0] & 0xffffff00);
  LOCK();
  piVar2 = (int *)(local_a4 + -4);
  iVar1 = *piVar2;
  *piVar2 = *piVar2 + -1;
  UNLOCK();
  if (iVar1 == 1 || iVar1 + -1 < 0) {
    (**(code **)(**(int **)(local_a4 + -0x10) + 4))((undefined4 *)(local_a4 + -0x10));
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group0_rgb",0xe);
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group1_rgb",0xe);
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group2_rgb",0xe);
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  pppcVar3 = local_48;
  if (0xf < local_34) {
    pppcVar3 = (char ***)local_48[0];
  }
  FUN_004481c0(local_9c,2,(char *)pppcVar3,local_38);
  pppcVar3 = local_30;
  if (0xf < local_1c) {
    pppcVar3 = (char ***)local_30[0];
  }
  FUN_004481c0(local_9c,3,(char *)pppcVar3,local_20);
  FUN_004482e0((int)local_9c);
  FUN_004056f0(local_48,(int *)"dpi_group3_rgb",0xe);
  FUN_00406540(&local_a0,0x54a358);
  pppcVar3 = (char ***)FUN_00404ce0((undefined1 *)local_60,&local_a0);
  if (local_30 != pppcVar3) {
    if (0xf < local_1c) {
      FUN_00405c80(local_30[0],local_1c + 1);
    }
    local_1c = 0xf;
    local_20 = 0;
    local_30[0] = (char **)((uint)local_30[0] & 0xffffff00);
    FUN_00405910(local_30,pppcVar3);
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  if (0xf < local_4c) {
    FUN_00405c80(local_60[0],local_4c + 1);
  }
  local_4c = 0xf;
  FUN_00405d20(local_60,0);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  uVar6 = local_38;
  pcVar4 = (char *)FUN_00405060(local_48);
  FUN_004481c0(local_9c,2,pcVar4,uVar6);
  uVar6 = local_20;
  pcVar4 = (char *)FUN_00405060(local_30);
  FUN_004481c0(local_9c,3,pcVar4,uVar6);
  FUN_004482e0((int)local_9c);
  FUN_00405070(local_48,(int *)"dpi_group4_rgb");
  FUN_00406540(&local_a0,0x54a358);
  puVar5 = (undefined4 *)FUN_00404ce0((undefined1 *)local_78,&local_a0);
  FUN_004050f0(local_30,puVar5);
  FUN_004050b0(local_78);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  uVar6 = local_38;
  pcVar4 = (char *)FUN_00405060(local_48);
  FUN_004481c0(local_9c,2,pcVar4,uVar6);
  uVar6 = local_20;
  pcVar4 = (char *)FUN_00405060(local_30);
  FUN_004481c0(local_9c,3,pcVar4,uVar6);
  FUN_004482e0((int)local_9c);
  FUN_00405070(local_48,(int *)"dpi_group5_rgb");
  FUN_00406540(&local_a0,0x54a358);
  puVar5 = (undefined4 *)FUN_00404ce0((undefined1 *)local_90,&local_a0);
  FUN_004050f0(local_30,puVar5);
  FUN_004050b0(local_90);
  FUN_004483f0(this,(int)local_9c,
               (byte *)"INSERT INTO t_configdata(profile, key, value) VALUES (?, ?, ?);",
               (byte *)0xffffffff);
  FUN_00448190(local_9c,1,param_1);
  uVar6 = local_38;
  pcVar4 = (char *)FUN_00405060(local_48);
  FUN_004481c0(local_9c,2,pcVar4,uVar6);
  uVar6 = local_20;
  pcVar4 = (char *)FUN_00405060(local_30);
  FUN_004481c0(local_9c,3,pcVar4,uVar6);
  FUN_004482e0((int)local_9c);
  FUN_00405430(&local_a0);
  FUN_004050b0(local_30);
  FUN_004050b0(local_48);
  FUN_00448030(local_9c);
  ExceptionList = local_10;
  __security_check_cookie(local_18 ^ (uint)&stack0xfffffffc);
  return;
}


