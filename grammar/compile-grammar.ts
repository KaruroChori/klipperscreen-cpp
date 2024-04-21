#!/bin/env bun
import { $ } from "bun"
const t = await $`cd ./grammar && ./node_modules/.bin/tree-sitter generate"`
