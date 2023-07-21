# `linux-uhid` - NodeJS bindings for Linux's UHID interface
[![npm version](https://badge.fury.io/js/linux-uhid.svg)](https://badge.fury.io/js/linux-uhid) [![License: GNU](https://img.shields.io/badge/License-GNU-blue.svg)](https://opensource.org/licenses/GNU)
`linux-uhid` is a NodeJS module that provides bindings for Linux's UHID interface. It allows you to create virtual HID devices and send input reports to them.

**NOTE:** Module *has* to be used with elevated privileges (root)!
## Installation
You can install `linux-uhid` via npm:

```bash
npm install linux-uhid
```
## Usage
```javascript
const uhid = require('linux-uhid');

var device = new UHIDDevice();

device.open();

device.create( {
	name: "node-uhid-device",
	data: Buffer.from( hid_descriptor ),
	bus: UHIDBusType.USB,
	vendor: 0x15d9,
	product: 0x0a37,
	version: 0x0001,
	country: 0x00
} );

// Send input report
device.input( Buffer.from( hid_input_report ));
```
Look at `test.ts` for an example of a mouse.
## Documentation
N/A (for now)
## TODO
- [ ] Add documentation.
- [x] Add TypeScript support.
- [ ] Look into adding support for reading /sys/kernel/debug/hid/<dev>/rdesc
