#!/usr/bin/env bash
# ==============================================================================
# Helper Script to Push Completed Labs to GitHub
# ==============================================================================
set -e

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$REPO_DIR"

echo "===================================================================="
echo "   Pushing Data Structures I Lab Assignments to GitHub             "
echo "   Target: https://github.com/Snehasen25220331/dsa-labsheet-       "
echo "===================================================================="
echo ""
echo "Note: GitHub requires a Personal Access Token (PAT) instead of password."
echo "If you haven't generated one yet, visit:"
echo "  https://github.com/settings/tokens (classic token with 'repo' scope)"
echo ""

read -p "Enter your GitHub Personal Access Token (PAT): " -s GITHUB_TOKEN
echo ""

if [ -z "$GITHUB_TOKEN" ]; then
    echo "[ERROR] No token entered. Push aborted."
    exit 1
fi

# Configure authenticated remote URL securely in-memory for the push
AUTH_REMOTE="https://Snehasen25220331:${GITHUB_TOKEN}@github.com/Snehasen25220331/dsa-labsheet-.git"

echo "Pushing branch 'main' to GitHub..."
git push -u "$AUTH_REMOTE" main

echo ""
echo "[SUCCESS] Successfully pushed all lab sheets to your repository!"
echo "Check your repo: https://github.com/Snehasen25220331/dsa-labsheet-"
echo ""
echo "Next step: Open a Pull Request to your teacher's repository:"
echo "  https://github.com/aradhyacse/Data-Structures-I-/compare/main...Snehasen25220331:dsa-labsheet-:main"
echo "===================================================================="
