; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noreturn nounwind uwtable
define dso_local void @app() local_unnamed_addr #0 {
  %1 = alloca [12 x i32], align 16
  %2 = alloca [12 x i32], align 16
  %3 = alloca [12 x i32], align 16
  %4 = alloca [12 x i32], align 16
  %5 = alloca [12 x i32], align 16
  call void @llvm.lifetime.start.p0(i64 48, ptr nonnull %1) #4
  call void @llvm.lifetime.start.p0(i64 48, ptr nonnull %2) #4
  call void @llvm.lifetime.start.p0(i64 48, ptr nonnull %3) #4
  call void @llvm.lifetime.start.p0(i64 48, ptr nonnull %4) #4
  call void @llvm.lifetime.start.p0(i64 48, ptr nonnull %5) #4
  br label %6

6:                                                ; preds = %0, %6
  %7 = phi i64 [ 0, %0 ], [ %43, %6 ]
  %8 = tail call i32 (...) @simRand() #4
  %9 = tail call i32 @llvm.abs.i32(i32 %8, i1 true)
  %10 = urem i32 %9, 1121
  %11 = add nuw nsw i32 %10, 80
  %12 = getelementptr inbounds [12 x i32], ptr %1, i64 0, i64 %7
  store i32 %11, ptr %12, align 4, !tbaa !5
  %13 = tail call i32 (...) @simRand() #4
  %14 = tail call i32 @llvm.abs.i32(i32 %13, i1 true)
  %15 = urem i32 %14, 631
  %16 = add nuw nsw i32 %15, 45
  %17 = getelementptr inbounds [12 x i32], ptr %2, i64 0, i64 %7
  store i32 %16, ptr %17, align 4, !tbaa !5
  %18 = tail call i32 (...) @simRand() #4
  %19 = tail call i32 @llvm.abs.i32(i32 %18, i1 true)
  %20 = and i32 %19, 3
  %21 = add nuw nsw i32 %20, 1
  %22 = tail call i32 (...) @simRand() #4
  %23 = and i32 %22, 1
  %24 = icmp eq i32 %23, 0
  %25 = xor i32 %20, -1
  %26 = select i1 %24, i32 %25, i32 %21
  %27 = getelementptr inbounds [12 x i32], ptr %3, i64 0, i64 %7
  store i32 %26, ptr %27, align 4, !tbaa !5
  %28 = tail call i32 (...) @simRand() #4
  %29 = tail call i32 @llvm.abs.i32(i32 %28, i1 true)
  %30 = and i32 %29, 3
  %31 = add nuw nsw i32 %30, 1
  %32 = tail call i32 (...) @simRand() #4
  %33 = and i32 %32, 1
  %34 = icmp eq i32 %33, 0
  %35 = xor i32 %30, -1
  %36 = select i1 %34, i32 %35, i32 %31
  %37 = getelementptr inbounds [12 x i32], ptr %4, i64 0, i64 %7
  store i32 %36, ptr %37, align 4, !tbaa !5
  %38 = tail call i32 (...) @simRand() #4
  %39 = tail call i32 @llvm.abs.i32(i32 %38, i1 true)
  %40 = urem i32 %39, 2001
  %41 = add nuw nsw i32 %40, 1000
  %42 = getelementptr inbounds [12 x i32], ptr %5, i64 0, i64 %7
  store i32 %41, ptr %42, align 4, !tbaa !5
  %43 = add nuw nsw i64 %7, 1
  %44 = icmp eq i64 %43, 12
  br i1 %44, label %45, label %6, !llvm.loop !9

45:                                               ; preds = %6, %75
  %46 = phi i64 [ %76, %75 ], [ 0, %6 ]
  %47 = getelementptr inbounds [12 x i32], ptr %1, i64 0, i64 %46
  %48 = load i32, ptr %47, align 4, !tbaa !5
  %49 = getelementptr inbounds [12 x i32], ptr %3, i64 0, i64 %46
  %50 = load i32, ptr %49, align 4, !tbaa !5
  %51 = add nsw i32 %50, %48
  %52 = getelementptr inbounds [12 x i32], ptr %2, i64 0, i64 %46
  %53 = load i32, ptr %52, align 4, !tbaa !5
  %54 = getelementptr inbounds [12 x i32], ptr %4, i64 0, i64 %46
  %55 = load i32, ptr %54, align 4, !tbaa !5
  %56 = add nsw i32 %55, %53
  %57 = icmp slt i32 %51, 0
  br i1 %57, label %60, label %58

58:                                               ; preds = %45
  %59 = icmp ugt i32 %51, 1279
  br i1 %59, label %60, label %63

60:                                               ; preds = %58, %45
  %61 = phi i32 [ 0, %45 ], [ 1279, %58 ]
  %62 = sub nsw i32 0, %50
  store i32 %62, ptr %49, align 4, !tbaa !5
  br label %63

63:                                               ; preds = %60, %58
  %64 = phi i32 [ %51, %58 ], [ %61, %60 ]
  %65 = icmp slt i32 %56, 0
  br i1 %65, label %68, label %66

66:                                               ; preds = %63
  %67 = icmp ugt i32 %56, 719
  br i1 %67, label %68, label %71

68:                                               ; preds = %66, %63
  %69 = phi i32 [ 0, %63 ], [ 719, %66 ]
  %70 = sub nsw i32 0, %55
  store i32 %70, ptr %54, align 4, !tbaa !5
  br label %71

71:                                               ; preds = %68, %66
  %72 = phi i32 [ %56, %66 ], [ %69, %68 ]
  store i32 %64, ptr %47, align 4, !tbaa !5
  store i32 %72, ptr %52, align 4, !tbaa !5
  %73 = add nuw nsw i64 %46, 1
  %74 = icmp eq i64 %73, 12
  br i1 %74, label %77, label %75

75:                                               ; preds = %71, %79
  %76 = phi i64 [ %73, %71 ], [ 0, %79 ]
  br label %45, !llvm.loop !11

77:                                               ; preds = %71, %82
  %78 = phi i32 [ %83, %82 ], [ 0, %71 ]
  br label %80

79:                                               ; preds = %82
  tail call void (...) @simFlush() #4
  br label %75

80:                                               ; preds = %77, %121
  %81 = phi i32 [ 0, %77 ], [ %130, %121 ]
  br label %87

82:                                               ; preds = %121
  %83 = add nuw nsw i32 %78, 1
  %84 = icmp eq i32 %83, 720
  br i1 %84, label %79, label %77, !llvm.loop !12

85:                                               ; preds = %87
  %86 = icmp ult i32 %104, 30
  br i1 %86, label %107, label %109

87:                                               ; preds = %80, %87
  %88 = phi i64 [ 0, %80 ], [ %105, %87 ]
  %89 = phi i32 [ 0, %80 ], [ %104, %87 ]
  %90 = getelementptr inbounds [12 x i32], ptr %1, i64 0, i64 %88
  %91 = load i32, ptr %90, align 4, !tbaa !5
  %92 = sub nsw i32 %81, %91
  %93 = getelementptr inbounds [12 x i32], ptr %2, i64 0, i64 %88
  %94 = load i32, ptr %93, align 4, !tbaa !5
  %95 = sub nsw i32 %78, %94
  %96 = mul nsw i32 %92, %92
  %97 = mul nsw i32 %95, %95
  %98 = add nuw nsw i32 %97, %96
  %99 = getelementptr inbounds [12 x i32], ptr %5, i64 0, i64 %88
  %100 = load i32, ptr %99, align 4, !tbaa !5
  %101 = udiv i32 %98, 100
  %102 = add nuw nsw i32 %101, 1
  %103 = udiv i32 %100, %102
  %104 = add i32 %103, %89
  %105 = add nuw nsw i64 %88, 1
  %106 = icmp eq i64 %105, 12
  br i1 %106, label %85, label %87, !llvm.loop !13

107:                                              ; preds = %85
  %108 = shl nuw nsw i32 %104, 1
  br label %121

109:                                              ; preds = %85
  %110 = icmp ult i32 %104, 80
  br i1 %110, label %111, label %115

111:                                              ; preds = %109
  %112 = mul nuw nsw i32 %104, 3
  %113 = add nsw i32 %112, -90
  %114 = add nuw nsw i32 %112, 10
  br label %121

115:                                              ; preds = %109
  %116 = icmp ult i32 %104, 160
  br i1 %116, label %117, label %121

117:                                              ; preds = %115
  %118 = mul nuw nsw i32 %104, 3
  %119 = add nsw i32 %118, -240
  %120 = sub nuw nsw i32 495, %118
  br label %121

121:                                              ; preds = %115, %111, %117, %107
  %122 = phi i32 [ 0, %107 ], [ %113, %111 ], [ %120, %117 ], [ 255, %115 ]
  %123 = phi i32 [ 0, %107 ], [ 0, %111 ], [ %119, %117 ], [ 255, %115 ]
  %124 = phi i32 [ %108, %107 ], [ %114, %111 ], [ 255, %117 ], [ 255, %115 ]
  %125 = shl nuw nsw i32 %122, 16
  %126 = shl nuw nsw i32 %124, 8
  %127 = or i32 %125, %123
  %128 = or i32 %127, %126
  %129 = or i32 %128, -16777216
  tail call void @simPutPixel(i32 noundef %81, i32 noundef %78, i32 noundef %129) #4
  %130 = add nuw nsw i32 %81, 1
  %131 = icmp eq i32 %130, 1280
  br i1 %131, label %82, label %80, !llvm.loop !14
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #2

declare void @simFlush(...) local_unnamed_addr #2

declare i32 @simRand(...) local_unnamed_addr #2

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.abs.i32(i32, i1 immarg) #3

attributes #0 = { noreturn nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = distinct !{!12, !10}
!13 = distinct !{!13, !10}
!14 = distinct !{!14, !10}
