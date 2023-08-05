# Modular BasicDrawDevice plugin for Kirikiri

This plugin provides BasicDrawDevice as a module for Kirikiri / 吉里吉里 2/Z

## Building

After cloning submodules and placing `ncbind` and `tp_stub` in the parent directory, a simple `make` will generate `BasicDrawDevice.dll`.

## How to use

After `Plugins.link("BasicDrawDevice.dll");` is used, the additional class will be available under `Window.BasicDrawDeviceModule`.

## License

This project is licensed under the MIT license. Please read the `LICENSE` file for more information.
