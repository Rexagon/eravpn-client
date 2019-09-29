# eravpn-client
Client For [EraVPN](http://eravpn.com/)

## How to build

### Windows
> Instructions will change in future. It looks ugly, but just works.

`Microsoft Visual Studio 2019` and `CMake` must be installed.

1. Build `openvpn3` somewhere using this 
[instruction](https://github.com/OpenVPN/openvpn3#building-the-openvpn-3-client-on-windows).

2. Define environment variables:
   ```
   MBEDTLS_INCLUDE_DIR=path/to/deps/amd64/mbedtls/include;
   TAP_WINDOWS_INCLUDE_DIR=path/to/deps/amd64/tap-windows/src;
   ASIO_INCLUDE_DIR=path/to/deps/amd64/asio/asio/include;
   LZ4_INCLUDE_DIR=path/to/deps/amd64/lz4/lib;
   OPENVPN_INCLUDE_path/to/ovpn3/core;
   
   MBEDTLS_LIBRARY=path/to/deps/amd64/mbedtls/library/mbedtls.lib;
   LZ4_LIBRARY=path/to/deps/amd64/lz4/lib/lz4.lib
   ```
   
3. Build application:
   ```shell script
   $ git clone https://github.com/Rexagon/eravpn-client.git
   $ cd eravpn-client
   $ mkdir temp && cd temp
   $ cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ..
   ```

### Mac 
`//TODO`
