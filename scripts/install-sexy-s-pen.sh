#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
mode="${1:-build}"

printf '%s\n' 'Sexy S-Pen installer'
printf '%s\n' 'This installer builds from the checked-out source and only asks for sudo during the final install step.'

case "$mode" in
  build)
    command -v cmake >/dev/null || { echo 'Missing cmake.' >&2; exit 1; }
    command -v ninja >/dev/null || { echo 'Missing ninja.' >&2; exit 1; }
    cmake -S "$repo_root" -B "$repo_root/build" -G Ninja -DCMAKE_BUILD_TYPE=Release
    cmake --build "$repo_root/build"
    sudo cmake --install "$repo_root/build"
    ;;
  flatpak)
    command -v flatpak-builder >/dev/null || { echo 'Install flatpak-builder first.' >&2; exit 1; }
    flatpak-builder --user --install --force-clean "$repo_root/.flatpak-build" "$repo_root/packaging/io.github.sexyspen.SexySPen.yml"
    ;;
  uninstall)
    sudo cmake --build "$repo_root/build" --target uninstall 2>/dev/null || sudo rm -f /usr/local/bin/sexy-s-pen
    ;;
  *)
    echo "Usage: $0 [build|flatpak|uninstall]" >&2
    exit 2
    ;;
esac
