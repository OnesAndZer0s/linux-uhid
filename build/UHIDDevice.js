"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.UHIDDevice = exports.UHIDReportType = exports.UHIDDevFlags = exports.UHIDBusType = void 0;
const bindings_1 = __importDefault(require("bindings"));
const uhid = (0, bindings_1.default)('linux-uhid');
const events_1 = require("events");
var UHIDBusType;
(function (UHIDBusType) {
    UHIDBusType[UHIDBusType["PCI"] = uhid.UHIDBusType.PCI] = "PCI";
    UHIDBusType[UHIDBusType["ISAPNP"] = uhid.UHIDBusType.ISAPNP] = "ISAPNP";
    UHIDBusType[UHIDBusType["USB"] = uhid.UHIDBusType.USB] = "USB";
    UHIDBusType[UHIDBusType["HIL"] = uhid.UHIDBusType.HIL] = "HIL";
    UHIDBusType[UHIDBusType["BLUETOOTH"] = uhid.UHIDBusType.BLUETOOTH] = "BLUETOOTH";
    UHIDBusType[UHIDBusType["VIRTUAL"] = uhid.UHIDBusType.VIRTUAL] = "VIRTUAL";
    UHIDBusType[UHIDBusType["ISA"] = uhid.UHIDBusType.ISA] = "ISA";
    UHIDBusType[UHIDBusType["I8042"] = uhid.UHIDBusType.I8042] = "I8042";
    UHIDBusType[UHIDBusType["XTKBD"] = uhid.UHIDBusType.XTKBD] = "XTKBD";
    UHIDBusType[UHIDBusType["RS232"] = uhid.UHIDBusType.RS232] = "RS232";
    UHIDBusType[UHIDBusType["GAMEPORT"] = uhid.UHIDBusType.GAMEPORT] = "GAMEPORT";
    UHIDBusType[UHIDBusType["PARPORT"] = uhid.UHIDBusType.PARPORT] = "PARPORT";
    UHIDBusType[UHIDBusType["AMIGA"] = uhid.UHIDBusType.AMIGA] = "AMIGA";
    UHIDBusType[UHIDBusType["ADB"] = uhid.UHIDBusType.ADB] = "ADB";
    UHIDBusType[UHIDBusType["I2C"] = uhid.UHIDBusType.I2C] = "I2C";
    UHIDBusType[UHIDBusType["HOST"] = uhid.UHIDBusType.HOST] = "HOST";
    UHIDBusType[UHIDBusType["GSC"] = uhid.UHIDBusType.GSC] = "GSC";
    UHIDBusType[UHIDBusType["ATARI"] = uhid.UHIDBusType.ATARI] = "ATARI";
    UHIDBusType[UHIDBusType["SPI"] = uhid.UHIDBusType.SPI] = "SPI";
    UHIDBusType[UHIDBusType["RMI"] = uhid.UHIDBusType.RMI] = "RMI";
    UHIDBusType[UHIDBusType["CEC"] = uhid.UHIDBusType.CEC] = "CEC";
    UHIDBusType[UHIDBusType["INTEL_ISHTP"] = uhid.UHIDBusType.INTEL_ISHTP] = "INTEL_ISHTP";
})(UHIDBusType = exports.UHIDBusType || (exports.UHIDBusType = {}));
var UHIDDevFlags;
(function (UHIDDevFlags) {
    UHIDDevFlags[UHIDDevFlags["FEATURE"] = uhid.UHIDDevFlags.NUMBERED_FEATURE_REPORTS] = "FEATURE";
    UHIDDevFlags[UHIDDevFlags["OUTPUT"] = uhid.UHIDDevFlags.NUMBERED_OUTPUT_REPORTS] = "OUTPUT";
    UHIDDevFlags[UHIDDevFlags["INPUT"] = uhid.UHIDDevFlags.NUMBERED_INPUT_REPORTS] = "INPUT";
})(UHIDDevFlags = exports.UHIDDevFlags || (exports.UHIDDevFlags = {}));
var UHIDReportType;
(function (UHIDReportType) {
    UHIDReportType[UHIDReportType["FEATURE"] = uhid.UHIDReportType.FEATURE_REPORT] = "FEATURE";
    UHIDReportType[UHIDReportType["OUTPUT"] = uhid.UHIDReportType.OUTPUT_REPORT] = "OUTPUT";
    UHIDReportType[UHIDReportType["INPUT"] = uhid.UHIDReportType.INPUT_REPORT] = "INPUT";
})(UHIDReportType = exports.UHIDReportType || (exports.UHIDReportType = {}));
class UHIDDevice extends uhid.UHIDDevice {
    constructor() {
        super();
        this.eE = new events_1.EventEmitter();
        this.eventEmitter = this.eE.emit.bind(this.eE);
    }
    on(event, listener) {
        this.eE.on(event, listener);
    }
    once(event, listener) {
        this.eE.once(event, listener);
    }
    off(event, listener) {
        this.eE.off(event, listener);
    }
    create(options) {
        super.create(options);
    }
    destroy() {
        super.destroy();
    }
    input(data) {
        super.input(data);
    }
    getReportReply(options) {
        super.getReportReply(options);
    }
    setReportReply(options) {
        super.setReportReply(options);
    }
    poll() {
        super.poll();
    }
    open() {
        super.open();
    }
    close() {
        super.close();
    }
}
exports.UHIDDevice = UHIDDevice;
