# Setting PATH for Python 3.6
# The original version is saved in .bash_profile.pysavea
PATH="/Library/Frameworks/Python.framework/Versions/3.6/bin:${PATH}"

# PATH for git-scm
PATH="/usr/local/git/bin:${PATH}"
export PATH

# Auto-complete for git
source /usr/local/git/contrib/completion/git-completion.bash

# Oracle Java
export JAVA_HOME=$(/usr/libexec/java_home)


[[ -s "$HOME/.rvm/scripts/rvm" ]] && source "$HOME/.rvm/scripts/rvm" # Load RVM into a shell session *as a function*

export PATH="$PATH:/Applications/Simplicity Studio.app/Contents/Eclipse/developer/adapter_packs/commander/Commander.app/Contents/MacOS"
export PATH="$PATH:/usr/local/gcc-arm-none-eabi-7-2017-q4-major/bin"

# Alias for Git Commands
alias gl='git log'
alias gll='git lola'
alias gs='git status'

# Alias for directories
alias ~='cd ~/'
alias w='cd ~/Workspace/'
alias p='cd ~/Projects/'

# Alias for ST-Link
alias stw='st-flash --reset write' # ex. stw EA31.bin 0x8000000
alias stwh='st-flash --reset --format ihex write'
alias ste='st-flash --reset erase'
alias str='st-flash --reset read' # ex. str EA31.bin 0x8000000 0x60000|384

# Alias for arm-gcc
alias b2h="arm-none-eabi-objcopy -I ihex --output-target=binary" # b2h code00.hex code00.bin
