# TensorFlowLiteC-binary
- 실리콘 맥에서 TensorFlowLite 2.5.0 버전 빌드를 위한 프로젝트
- https://github.com/revolut-mobile/TensorFlowLiteC-binary 프로젝트를 참고하여 수정
- Sonoma, XCode 15.3 환경

## 사용법
1. `git clone dev-gloomyfox/TensorFlowLiteC-binary`
2. `cd {clone_repository}`
3. `cd build/bazel/3.7.2`
4. bazel에서 사용할 파이썬 인터프리터 변경이 필요
  - `build/bazel/3.7.2/src/main/java/com/google/devtools/build/lib/bazel/rules/python/python_stub_template.txt` 수정
  - 최상단의 `#!/usr/bin/env /Users/gloomyfox/miniforge3/bin/python` 부분을 `#!/usr/bin/env {USER_PYTHON_INTERPRETER_PATH}`로 변경
5. bazel 빌드: `../4.1.0/bazel build --incompatible_restrict_string_escapes=false --incompatible_linkopts_to_linklibs=false -c opt //src:bazel`
  - 이 단계에서 `File not found: /Applications/Xcode-beta.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/arc/libarclite_iphoneos.a` 등의 libarclite 라이브러리 관련 에러가 발생 가능, 아래 방식으로 해결
    ```
    cd /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/
    # Preferences → Security & Privacy → Full Disk Access → Terminal
    sudo mkdir arc
    cd  arc
    sudo git clone https://github.com/kamyarelyasi/Libarclite-Files.git .
    sudo chmod +x *
    ```
6. `cd {clone_repository}`
7. `make`
8. 정상 작동하면 `build/output` 아래에 xcframework 생성

## 변경한 부분
- 아래 나열한 부분은 변경한 내용으로 해당 부분을 스크립트에 반영 가능할 듯
- 스크립트 실행 시 다운받던 부분들 제거하고 이미 모두 다운받은 상태에서 실행하게 변경
- bazel 빌드 및 패치 부분을 직접 실행하게 변경: 파이썬 인터프리터 이슈 때문에 해당 방식으로 일단 수정
- build/bazel/3.7.2/thirdparty/zlib/BUILD, build/bazel/3.7.2/thirdparty/zlib/BUILD.tools 변경
  - XCode 버전 올라감에 따라 암시적 함수 사용시 에러뜨는 부분을 해결
    - "-Wno-deprecated-non-prototype", "-Wno-unused-variable", "-Wno-implicit-function-declaration" 옵션을 추가한 방식
- bazel 빌드 실행 시 XCode 버전 올라감에 따라 발생하는 프로토버퍼 쪽 문제해결하기 위해 `--incompatible_linkopts_to_linklibs=false` 옵션 추가
