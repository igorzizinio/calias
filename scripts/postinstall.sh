#!/bin/sh

ALIAS_LINE='source ~/.caliases'

update_shell_rc() {
  RC_FILE="$1"

  if [ -f "$RC_FILE" ]; then
    if ! grep -Fxq "$ALIAS_LINE" "$RC_FILE"; then
      echo "# Load custom aliases from calias" >>"$RC_FILE"
      echo "$ALIAS_LINE" >>"$RC_FILE"
      echo "✅ Added to $RC_FILE"
    else
      echo "ℹ️ Already present in $RC_FILE"
    fi
  fi
}

update_shell_rc "$HOME/.bashrc"
update_shell_rc "$HOME/.zshrc"
