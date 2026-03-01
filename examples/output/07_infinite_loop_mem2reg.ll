; ModuleID = 'output/07_infinite_loop_output.ll'
source_filename = "07_infinite_loop.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local noundef i32 @_Z18infinite_loop_testv() #0 {
entry:
  br label %while.body

while.body:                                       ; preds = %if.end, %entry
  %count.0 = phi i32 [ 0, %entry ], [ %inc, %if.end ]
  %inc = add nsw i32 %count.0, 1
  %cmp = icmp sgt i32 %inc, 1000000
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %while.body
  br label %while.end

if.end:                                           ; preds = %while.body
  br label %while.body, !llvm.loop !6

while.end:                                        ; preds = %if.then
  ret i32 %inc
}

; Function Attrs: mustprogress noinline nounwind uwtable
define dso_local void @_Z14truly_infinitev() #0 {
entry:
  br label %while.body

while.body:                                       ; preds = %while.body, %entry
  %x.0 = phi i32 [ 0, %entry ], [ %rem, %while.body ]
  %add = add nsw i32 %x.0, 1
  %rem = srem i32 %add, 100
  br label %while.body, !llvm.loop !8
}

; Function Attrs: mustprogress noinline norecurse nounwind uwtable
define dso_local noundef i32 @main() #1 {
entry:
  call void @_Z14truly_infinitev()
  %call = call noundef i32 @_Z18infinite_loop_testv()
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
