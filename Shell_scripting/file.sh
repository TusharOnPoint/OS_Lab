read -p "Enter a file name: " file
if [ -e "$file" ]; then
    echo "$file exists."
else
    echo "$file does not exist. Creating $file..."
    touch "$file"
    echo "$file created successfully."
fi

if [ -x "$file" ]; then
    echo "$file has execution permission."
else
    echo "$file does not have execution permission"
    echo "Giving execution permission to $file"
    chmod +x "$file"
fi

