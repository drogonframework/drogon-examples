/**
 * @brief bundle type class
 * @type {self}
 */
export class Bundle_t {
    /** @type {string} */  name;
    /** @type {string} */  source;
    /** @type {string} */  format;
    /** @type {boolean} */ is_production;

    /**
     * @param {string} _name 
     * @param {string} _source 
     * @param {string} _format 
     * @param {boolean} _production 
     */
    constructor(_name, _source, _format, _production) {
        this.name = _name;
        this.source = _source;
        this.format = _format;
        this.is_production = _production;
    }
};
