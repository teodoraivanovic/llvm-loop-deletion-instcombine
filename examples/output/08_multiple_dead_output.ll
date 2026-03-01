; ModuleID = '08_multiple_dead.cpp'
source_filename = "08_multiple_dead.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z19multiple_dead_loopsv() #0 {
entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %c = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 0, i32* %b, align 4
  store i32 0, i32* %c, align 4
  store i32 0, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4
  %cmp = icmp slt i32 %0, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %i, align 4
  %2 = load i32, i32* %a, align 4
  %add = add nsw i32 %2, %1
  store i32 %add, i32* %a, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %3 = load i32, i32* %i, align 4
  %inc = add nsw i32 %3, 1
  store i32 %inc, i32* %i, align 4
  br label %for.cond, !llvm.loop !6

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %j, align 4
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc5, %for.end
  %4 = load i32, i32* %j, align 4
  %cmp2 = icmp slt i32 %4, 20
  br i1 %cmp2, label %for.body3, label %for.end7

for.body3:                                        ; preds = %for.cond1
  %5 = load i32, i32* %j, align 4
  %mul = mul nsw i32 %5, 2
  %6 = load i32, i32* %b, align 4
  %add4 = add nsw i32 %6, %mul
  store i32 %add4, i32* %b, align 4
  br label %for.inc5

for.inc5:                                         ; preds = %for.body3
  %7 = load i32, i32* %j, align 4
  %inc6 = add nsw i32 %7, 1
  store i32 %inc6, i32* %j, align 4
  br label %for.cond1, !llvm.loop !8

for.end7:                                         ; preds = %for.cond1
  store i32 0, i32* %k, align 4
  br label %for.cond8

for.cond8:                                        ; preds = %for.inc13, %for.end7
  %8 = load i32, i32* %k, align 4
  %cmp9 = icmp slt i32 %8, 5
  br i1 %cmp9, label %for.body10, label %for.end15

for.body10:                                       ; preds = %for.cond8
  %9 = load i32, i32* %c, align 4
  %mul11 = mul nsw i32 %9, 3
  %add12 = add nsw i32 %mul11, 1
  store i32 %add12, i32* %c, align 4
  br label %for.inc13

for.inc13:                                        ; preds = %for.body10
  %10 = load i32, i32* %k, align 4
  %inc14 = add nsw i32 %10, 1
  store i32 %inc14, i32* %k, align 4
  br label %for.cond8, !llvm.loop !9

for.end15:                                        ; preds = %for.cond8
  ret i32 12345
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  %call = call noundef i32 @_Z19multiple_dead_loopsv()
  ret i32 %call
}

attributes #0 = { mustprogress noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress noinline norecurse nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 1}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 14.0.0-1ubuntu1.1"}
!6 = distinct !{!6, !7}
!7 = !{!"llvm.loop.mustprogress"}
!8 = distinct !{!8, !7}
!9 = distinct !{!9, !7}
