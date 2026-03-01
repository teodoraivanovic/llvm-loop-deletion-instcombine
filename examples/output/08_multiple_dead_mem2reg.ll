; ModuleID = 'output/08_multiple_dead_output.ll'
source_filename = "08_multiple_dead.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z19multiple_dead_loopsv() #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %a.0 = phi i32 [ 0, %entry ], [ %add, %for.inc ]
  %cmp = icmp slt i32 %i.0, 10
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %add = add nsw i32 %a.0, %i.0
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond, !llvm.loop !6

for.end:                                          ; preds = %for.cond
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc5, %for.end
  %j.0 = phi i32 [ 0, %for.end ], [ %inc6, %for.inc5 ]
  %b.0 = phi i32 [ 0, %for.end ], [ %add4, %for.inc5 ]
  %cmp2 = icmp slt i32 %j.0, 20
  br i1 %cmp2, label %for.body3, label %for.end7

for.body3:                                        ; preds = %for.cond1
  %mul = mul nsw i32 %j.0, 2
  %add4 = add nsw i32 %b.0, %mul
  br label %for.inc5

for.inc5:                                         ; preds = %for.body3
  %inc6 = add nsw i32 %j.0, 1
  br label %for.cond1, !llvm.loop !8

for.end7:                                         ; preds = %for.cond1
  br label %for.cond8

for.cond8:                                        ; preds = %for.inc13, %for.end7
  %k.0 = phi i32 [ 0, %for.end7 ], [ %inc14, %for.inc13 ]
  %c.0 = phi i32 [ 0, %for.end7 ], [ %add12, %for.inc13 ]
  %cmp9 = icmp slt i32 %k.0, 5
  br i1 %cmp9, label %for.body10, label %for.end15

for.body10:                                       ; preds = %for.cond8
  %mul11 = mul nsw i32 %c.0, 3
  %add12 = add nsw i32 %mul11, 1
  br label %for.inc13

for.inc13:                                        ; preds = %for.body10
  %inc14 = add nsw i32 %k.0, 1
  br label %for.cond8, !llvm.loop !9

for.end15:                                        ; preds = %for.cond8
  ret i32 12345
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
entry:
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
