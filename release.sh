#!/bin/bash

#
# release.sh
# MRTCSDK-iOS —— 自动化发布脚本
#
# 功能：自动完成 Git 提交、打标签、CocoaPods 发布流程
#

set -e # 任何命令失败时退出脚本

# ==================== 颜色输出 ====================
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# ==================== 辅助函数 ====================

print_info() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

print_success() {
    echo -e "${GREEN}✅ $1${NC}"
}

print_warning() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

print_error() {
    echo -e "${RED}❌ $1${NC}"
}

print_section() {
    echo ""
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "${BLUE}  $1${NC}"
    echo -e "${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo ""
}

# ==================== 参数解析 ====================

COMMIT_MESSAGE=""
VERSION=""
SKIP_GIT=false
SKIP_POD=false

usage() {
    echo "用法: $0 [选项]"
    echo ""
    echo "选项:"
    echo "  -m, --message <message>   Git 提交信息 (必需)"
    echo "  -v, --version <version>   版本号 (必需, 如: 2.1.2)"
    echo "  --skip-git               跳过 Git 提交和推送"
    echo "  --skip-pod               跳过 CocoaPods 发布"
    echo "  -h, --help               显示帮助信息"
    echo ""
    echo "示例:"
    echo "  $0 -m '支持虚拟背景' -v 2.1.2"
    echo "  $0 -m '修复 bug' -v 2.1.3 --skip-git"
    echo ""
    exit 1
}

while [[ $# -gt 0 ]]; do
    case $1 in
        -m|--message)
            COMMIT_MESSAGE="$2"
            shift 2
            ;;
        -v|--version)
            VERSION="$2"
            shift 2
            ;;
        --skip-git)
            SKIP_GIT=true
            shift
            ;;
        --skip-pod)
            SKIP_POD=true
            shift
            ;;
        -h|--help)
            usage
            ;;
        *)
            print_error "未知参数: $1"
            usage
            ;;
    esac
done

# ==================== 参数校验 ====================

if [ -z "$COMMIT_MESSAGE" ]; then
    print_error "缺少 Git 提交信息"
    usage
fi

if [ -z "$VERSION" ]; then
    print_error "缺少版本号"
    usage
fi

# ==================== 版本号校验 ====================

print_section "版本号校验"

PODSPEC_FILE="MRTCSDK.podspec"
if [ ! -f "$PODSPEC_FILE" ]; then
    print_error "找不到 podspec 文件: $PODSPEC_FILE"
    exit 1
fi

# 从 podspec 文件中提取版本号
PODSPEC_VERSION=$(grep -E '^\s*spec\.version\s*=' "$PODSPEC_FILE" | sed -n 's/.*"\([^"]*\)".*/\1/p')

print_info "Podspec 版本号: $PODSPEC_VERSION"
print_info "输入版本号: $VERSION"

if [ "$PODSPEC_VERSION" != "$VERSION" ]; then
    print_error "版本号不匹配！"
    print_error "Podspec 中版本为 $PODSPEC_VERSION, 但输入版本为 $VERSION"
    print_info "请先更新 podspec 文件中的版本号"
    exit 1
fi

print_success "版本号校验通过"

# ==================== Git 操作 ====================

if [ "$SKIP_GIT" = false ]; then
    print_section "Git 操作"

    # 检查是否有未提交的更改（包括未跟踪的文件）
    if git diff-index --quiet HEAD -- && [ -z "$(git ls-files --others --exclude-standard)" ]; then
        print_warning "没有需要提交的更改"
    else
        # 显示将要提交的文件
        print_info "以下文件将被提交:"
        echo ""
        git status --short
        echo ""
        
        # 询问确认
        read -p "$(echo -e ${YELLOW}是否继续提交? [y/N]: ${NC})" -n 1 -r
        echo ""
        if [[ ! $REPLY =~ ^[Yy]$ ]]; then
            print_warning "取消发布"
            exit 0
        fi
        
        print_info "提交代码..."
        git add .
        git commit -m "$COMMIT_MESSAGE"
        print_success "代码提交成功"
    fi

    # 推送到远程
    print_info "推送到远程仓库..."
    git push
    print_success "代码推送成功"

    # 检查 tag 是否已存在
    if git tag -l | grep -q "^${VERSION}$"; then
        print_error "Tag $VERSION 已存在"
        print_info "如需重新发布,请先删除旧 tag:"
        print_info "  git tag -d $VERSION"
        print_info "  git push origin :refs/tags/$VERSION"
        exit 1
    fi

    # 创建并推送 tag
    print_info "创建 tag $VERSION..."
    git tag "$VERSION"
    git push --tags
    print_success "Tag 创建并推送成功"
fi

# ==================== CocoaPods 发布 ====================

if [ "$SKIP_POD" = false ]; then
    print_section "CocoaPods 发布"

    # 校验 podspec
    print_info "校验 podspec 文件..."
    print_info "执行: pod spec lint $PODSPEC_FILE --allow-warnings --use-libraries --no-clean --verbose --skip-import-validation"
    
    if pod spec lint "$PODSPEC_FILE" --allow-warnings --use-libraries --no-clean --verbose --skip-import-validation; then
        print_success "Podspec 校验通过"
    else
        print_error "Podspec 校验失败"
        exit 1
    fi

    # 推送到 CocoaPods Trunk
    print_info "推送到 CocoaPods Trunk..."
    print_info "执行: pod trunk push $PODSPEC_FILE --allow-warnings --use-libraries --verbose --skip-import-validation"
    
    if pod trunk push "$PODSPEC_FILE" --allow-warnings --use-libraries --verbose --skip-import-validation; then
        print_success "CocoaPods 发布成功"
    else
        print_error "CocoaPods 发布失败"
        exit 1
    fi
fi

# ==================== 发布完成 ====================

print_section "发布完成"

print_success "🎉 MRTCSDK $VERSION 发布成功！"
echo ""
print_info "发布信息:"
echo "  - 版本号: $VERSION"
echo "  - 提交信息: $COMMIT_MESSAGE"
echo "  - Git Tag: $VERSION"
echo "  - CocoaPods: MRTCSDK/$VERSION"
echo ""
print_info "使用方式:"
echo "  pod 'MRTCSDK', '~> $VERSION'"
echo ""
