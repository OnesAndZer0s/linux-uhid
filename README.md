# linux-uhid
NodeJS bindings for Linux's UHID interface.

**NOTE:** Module *has* to be used with elevated privileges (root)!
## Installation
```bash
npm install linux-uhid
```
## Usage
```javascript
const uhid = require('linux-uhid');

// Create a new device
var device = new UHIDDevice();
// open device
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
Look at `test.ts` for examples.
## Todo
- [ ] Add documentation.
- [x] Add TypeScript support.
- [ ] Look into adding support for reading /sys/kernel/debug/hid/<dev>/rdesc
